"""
Methods for assessing models

Copyright (c) 2015- Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

from __future__ import print_function
import sys

import numpy as np
import pandas as pd


class ErrStats(object):

    def __init__(self, **kwargs):
        # pessimistic initialization
        self.highest = kwargs.get('highest', 0.)
        self.lowest = kwargs.get('lowest', 1.)
        self.average = kwargs.get('average', None)

class EinEout(object):

    def __init__(self, **kwargs):
        self.ein = kwargs.get('ein', ErrStats())
        self.eout = kwargs.get('eout', ErrStats())

def _get_partitioned_data(features, labels, partition, ix, preprocessfn):
    """ separate training and test data using `partition` and `ix` """
    mask = (partition != ix)
    feattrain = features[mask, :]
    labtrain = labels[mask, :]
    feattest = features[~mask, :]
    labtest = labels[~mask, :]
    if preprocessfn is not None:
        feattrain, feattest = preprocessfn(feattrain, feattest)
    return feattrain, labtrain, feattest, labtest

def _update_summaries(summaries, ein, eout):
    for i in range(len(summaries)):
        _update_hilo(summaries[i].ein, ein[0, i])
        _update_hilo(summaries[i].eout, eout[0, i])

def _update_hilo(err_sum, current_err):
    if err_sum.highest < current_err:
        err_sum.highest = current_err
    if err_sum.lowest > current_err:
        err_sum.lowest = current_err

def multi_xval(features, labels, n_parts, partition, modelfn, errorfn,
        preprocessfn=None):
    """
    Evaluate models generated by modelfn using the given 
    partition to separate training and validation data.

    Parameters
    --
    features : ndarray
        Feature set.

    labels : ndarray
        Labels corresponding to the given features.

    n_parts : int
        Number of partitions. The integers in the `partition`
        array should all be >= 0 and < `n_parts`.

    partition : ndarray
        Random numbers in `range(n_parts)` having the same
        number of rows as `features` and `labels` and 1 column.

    modelfn : function
        Function used to generate models from features and labels.

    errorfn : function
        Function for evaluating error. Should take as arguments
        predictions and actual labels and return a metric quantifying
        the errors. For example: `pl.error.stderr(predicted, actual)`.

    preprocessfn : function, optional
        Function for adjusting features, such as centering or
        normalization functions. Function must take training
        features and test features as arguments and return the
        same with adjustments.

    Returns
    --
    results : list {object}
        A list of object containing average, lowest and highest
        errors for ein and eout.
    """
    _results = [EinEout() for i in range(labels.shape[1])]
    _ein_tot = np.zeros((1, labels.shape[1]))
    _eout_tot = np.zeros((1, labels.shape[1]))
    for i in range(n_parts):
        _feattrain, _labtrain, _feattest, _labtest = _get_partitioned_data(features, 
                labels, partition, i, preprocessfn)
        # get _results
        print('.', end="")
        sys.stdout.flush()
        _model = modelfn(_feattrain, _labtrain)
        _predtrain = _model.predict(_feattrain)
        _ein = errorfn(_predtrain, _labtrain)
        _ein_tot += _ein
        _predtest = _model.predict(_feattest)
        _eout = errorfn(_predtest, _labtest)
        _eout_tot += _eout
        _update_summaries(_results, _ein, _eout)
    # update averages
    for i in range(labels.shape[1]):
        _results[i].ein.average = 0.1 * _ein_tot[0, i]
        _results[i].eout.average = 0.1 * _eout_tot[0, i]
    print('.')
    sys.stdout.flush()
    return _results