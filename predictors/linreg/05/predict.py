"""
Baseline algorithm: Constant prediction

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

from __future__ import print_function
from functools import partial
import os
import sys

import numpy as np
import pandas as pd

sys.path.append('../')
import settings
sys.path.append('../common')
import baseline
import data
from metrics import EinEout
import pylearn as pl
import report

def get_alldata():
    """ Return features, labels combined for all equities """
    eqfile = "../{0}/equities.csv".format(settings.DATA_ROOT)
    equities = data.get_equities(eqfile)
    n_feat_sess = 0
    # powers of 2 from 0 to 6: 1, 2, 4, 8, 16, 32, 64
    n_pred_intervals = 7
    featurecols = ['Adj Close']
    labelcol = 'Adj Close'
    startdate = '1995-01-01'
    enddate = '2015-01-01'
    fname = "../{0}/features/{1}/labels/real/multi/{2}/combined.npy".format(settings.DATA_ROOT,
            n_feat_sess, n_pred_intervals) 
    # retrieve from file if it exists
    if os.path.isfile(fname):
        return data.load(fname, n_pred_intervals)
    # otherwise build and save to file
    directory = os.path.dirname(fname)
    if not os.path.exists(directory):
        os.makedirs(directory)
    features, labels = data.aggregate(equities, startdate, enddate, const_feat_only, 
            partial(data.multi_period_growth, n_pred_intervals, 'Adj Close'))
    data.save(fname, features, labels)
    return features, labels

def const_feat_only(eqdata):
    """
    Return a dataframe of appropriate size that
    has nothing but the constant feature `1`
    """
    _df = pd.DataFrame(data=np.ones((len(eqdata.index), 1)), index=eqdata.index, columns=['Const'])
    return _df, 0

def get_partitioned_data(features, labels, partition, ix):
    """ separate training and test data using `partition` and `ix` """
    mask = (partition != ix)
    feattrain = features[mask, :]
    labtrain = labels[mask, :]
    feattest = features[~mask, :]
    labtest = labels[~mask, :]
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

def evaluate_model(features, labels, partition):
    results = [EinEout() for i in range(labels.shape[1])]
    baseein_tot = np.zeros((1, labels.shape[1]))
    baseeout_tot = np.zeros((1, labels.shape[1]))
    basegrowth_tot = np.zeros((1, labels.shape[1]))
    for i in range(10):
        feattrain, labtrain, feattest, labtest = get_partitioned_data(features, labels, partition, i)
        # get results for baseline    
        print('.', end="")
        sys.stdout.flush()
        model = baseline.get_model(feattrain, labtrain)
        basegrowth_tot += model[0, :]
        predtrain = baseline.predict(feattrain, model)
        ein = pl.error.stderr(predtrain, labtrain)
        baseein_tot += ein
        predtest = baseline.predict(feattest, model)
        eout = pl.error.stderr(predtest, labtest)
        baseeout_tot += eout
        _update_summaries(results, ein, eout)
    # update averages
    for i in range(labels.shape[1]):
        results[i].ein.average = 0.1 * baseein_tot[0, i]
        results[i].eout.average = 0.1 * baseeout_tot[0, i]
        ave_base_growth = 0.1 * basegrowth_tot
    print('.')
    sys.stdout.flush()
    return results, ave_base_growth

def save_results(results, baseline_growth):
    fname = "RESULTS.md"
    content = report.errors_by_dist(results, baseline_growth, [2**i for i in range(7)])
    with open(fname, 'w') as f:
        f.write(content)

def run():
    print("Retrieving data")
    features, labels = get_alldata()
    pfile = "../{0}/partition.csv".format(settings.DATA_ROOT)
    partition = data.partition(pfile, features.shape[0])
    print("Evaluating model")
    results, baseline_growth = evaluate_model(features, labels, partition)
    return results, baseline_growth

if __name__ == "__main__":
    results, baseline_growth = run()
    save_results(results, baseline_growth)
