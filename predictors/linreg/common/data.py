"""
Functions for assembling data sets for linear regression

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import os

import numpy as np
import pandas as pd
import pynance as pn

def get_equities(fname):
    with open(fname) as f:
        equities = f.read().splitlines()
    return equities

def partition(fname, size, nparts=10):
    """
    Return and, if necessary, save an ndarray of the given size with 
    integer values randomly sampled from [0, nparts).
    If such an array has already been saved to file, the
    contents of the file will be returned as an ndarray. If not,
    a random array of the given size will be generated and saved
    for future use.

    To be used for partitioning data in a random
    yet reproducible manner.
    """
    if os.path.isfile(fname):
        randpart = np.loadtxt(fname, dtype=int)[:size]
        if len(randpart) < size:
            raise ValueError("saved file too small")
    else:
        randpart = np.random.randint(nparts, size=size)
        np.savetxt(fname, randpart, fmt="%d")
    return randpart

def get_eqfeatures(data, n_feat_sess, prediction_interval, data_col, startdate, enddate):
    """
    Return a DataFrame containing the specified features for the given
    data set.
    """
    return pn.data.featurize(data, n_feat_sess, 
            selection=data_col).iloc[:-prediction_interval, :]

def get_eqlabels(data, n_feat_sess, prediction_interval, data_col, startdate, enddate):
    """
    Return a DataFrame containing the specified labels for the given
    data set.
    """
    labeldata = data.loc[:, data_col].values[(n_feat_sess + prediction_interval - 1):] / \
            data.loc[:, data_col].values[(n_feat_sess - 1):-prediction_interval]
    labels = pd.DataFrame(data=labeldata, index=data.index[(n_feat_sess - 1):-prediction_interval],
            columns=['Return Ratio'], dtype='float64')
    return labels

def build_alldata(equities, n_feat_sess, prediction_interval, featurecols, labelcol, startdate, enddate):
    """
    Return an ndarray of features combining the data for all `equities` using the
    given parameters and a vector of labels.

    Features are normalized, and the constant feature is prepended.

    Parameters
    --
    selection : list of strings
        columns to use from DataFrame retrieved for each equity
    """
    features = np.empty((0, n_feat_sess * len(featurecols)))
    labels = np.empty((0, 1))
    for equity in equities:
        data = pn.data.get(equity, startdate, enddate)
        print("{0} records retrieved for equity '{1}'".format(len(data.index), equity))
        # get labels as DataFrame
        eqlab = get_eqlabels(data, n_feat_sess, prediction_interval, labelcol, startdate, enddate)
        # create an empty ndarray with the correct number of rows and 0 columns
        eqfeatall = np.empty((data.shape[0] - n_feat_sess - prediction_interval + 1, 0))
        for featcol in featurecols:
            eqfeat = get_eqfeatures(data, n_feat_sess, prediction_interval, featcol, startdate, enddate)
            eqfeat = pn.data.normalize(eqfeat, method="mean")
            eqfeatall = np.append(eqfeatall, eqfeat.values, axis=1)
        features = np.append(features, eqfeatall, axis=0)
        labels = np.append(labels, eqlab.values, axis=0)
    features = pn.data.add_const(features)
    return features, labels

def save(fname, features, labels):
    # combine features and labels into a single ndarray
    data = np.empty((features.shape[0], features.shape[1] + labels.shape[1]))
    data[:, :labels.shape[1]] = labels
    data[:, labels.shape[1]:] = features
    # save the result
    np.save(fname, data)

def load(fname, n_labelcols=1):
    """
    Retrieve features and labels from csv file
    """
    #data = np.loadtxt(fname, delimiter=',', dtype='float64')
    data = np.load(fname)
    return data[:, n_labelcols:], data[:, :n_labelcols]

def multi_period_growth(n_periods, pricecol, eqdata):
    """
    Function to be passed using partial to `pn.data.labeledfeatures()`
    """
    _skipatend = 2**(n_periods - 1)
    _size = len(eqdata.index)
    _cols = map(str, map(lambda n: 2**n, range(n_periods)))
    _all_labs = pd.DataFrame(index=eqdata.index[:-_skipatend], columns=_cols, dtype=np.float64)
    for i in range(n_periods):
        _df, _ = pn.data.lab.growth(2**i, pricecol, eqdata)
        _all_labs.iloc[:, i] = _df.iloc[:(_size - _skipatend), 0]
    return _all_labs, _skipatend

def aggregate(equities, startdate, enddate, featurefunc, labelfunc):
    """
    Aggregate data for all of the given equities
    """
    _eqdata = pn.data.get(equities[0], startdate, enddate)
    _featdf, _labdf = pn.data.labeledfeatures(_eqdata, featurefunc, labelfunc)
    _features = _featdf.values
    _labels = _labdf.values
    for i in range(1, len(equities)):
        _eqdata = pn.data.get(equities[i], startdate, enddate)
        print("{0} records retrieved for equity '{1}'".format(len(_eqdata.index), equities[i]))
        _featdf, _labdf = pn.data.labeledfeatures(_eqdata, featurefunc, labelfunc)
        _features = np.append(_features, _featdf.values, axis=0)
        _labels = np.append(_labels, _labdf.values, axis=0)
    return _features, _labels
