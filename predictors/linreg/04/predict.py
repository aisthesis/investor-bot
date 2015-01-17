"""
Linear regression with centered and normalized data.

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
import pynance as pn

sys.path.append('../')
import settings
sys.path.append('../common')
import data
from metrics import ErrorSummary
import pylearn as pl

def get_alldata():
    """ Return features, labels combined for all equities """
    eqfile = "../{0}/equities.csv".format(settings.DATA_ROOT)
    equities = data.get_equities(eqfile)
    n_feat_sess = 256
    prediction_interval = 64
    featurecols = ['Adj Close', 'Volume']
    labelcol = 'Adj Close'
    startdate = '1960-01-01'
    enddate = '2014-12-11'
    fname = "../{0}/growth/relvol/features/{1}/labels/real/{2}/combined.npy".format(settings.DATA_ROOT,
            n_feat_sess, prediction_interval) 
    # retrieve from file if it exists
    if os.path.isfile(fname):
        return data.load(fname)
    # otherwise build and save to file
    directory = os.path.dirname(fname)
    if not os.path.exists(directory):
        os.makedirs(directory)
    features, labels = _build_data(equities, n_feat_sess, prediction_interval, startdate, enddate)
    data.save(fname, features, labels)
    return features, labels

def _build_data(equities, n_feat_sess, prediction_interval, startdate, enddate):
    """ Build features and labels to be used in current run.  """
    features = np.empty((0, 2 * n_feat_sess))
    labels = np.empty((0, 1))
    for equity in equities:
        print("Building features and labels for equity '{0}'".format(equity))
        sys.stdout.flush()
        eqfeat, eqlab = _build_eqdata(equity, n_feat_sess, prediction_interval, 
                startdate, enddate)
        features = np.append(features, eqfeat.values, axis=0)
        labels = np.append(labels, eqlab.values, axis=0)
    features = pn.data.add_const(features)
    return features, labels

def _build_eqdata(equity, n_feat_sess, prediction_interval, startdate, enddate):
    """ Build features and labels for given equity """
    eqdata = pn.data.get(equity, startdate, enddate)
    ave_interval = 2
    growth = _get_daily_growth(eqdata, skipstartrows=(ave_interval - 1), 
            skipendrows=prediction_interval)
    volume = _get_ratio_to_ave(eqdata, skipendrows=prediction_interval, 
            ave_interval=ave_interval)
    features = _build_features(growth, volume, n_feat_sess)
    labels = _get_labels(eqdata, prediction_interval, skiprows=(ave_interval + n_feat_sess - 1))
    return features, labels

def _build_features(growth, volume, n_feat_sess):
    growth_feat = pn.data.featurize(growth, n_feat_sess, selection='Daily Growth')
    vol_feat = pn.data.featurize(volume, n_feat_sess, selection='Rel Vol')
    growth_cols = map(partial(_concat, strval='G'), range(-n_feat_sess + 1, 1))
    vol_cols = map(partial(_concat, strval='V'), range(-n_feat_sess + 1, 1))
    feature_cols = list(growth_cols) + list(vol_cols)
    features = pd.DataFrame(index=growth_feat.index, columns=feature_cols,
            dtype='float64')
    features.iloc[:, :n_feat_sess] = growth_feat.values
    features.iloc[:, n_feat_sess:] = vol_feat.values
    return features

def _concat(intval, strval):
    return str(intval) + strval

def _get_labels(eqdata, prediction_interval, skiprows=0):
    col = 'Adj Close'
    labeldata = eqdata.loc[:, col].values[(skiprows + prediction_interval):] / \
            eqdata.loc[:, col].values[skiprows:-prediction_interval]
    return pd.DataFrame(data=labeldata, index=eqdata.index[skiprows:-prediction_interval],
            columns=['Growth'], dtype='float64')

def _get_daily_growth(eqdata, skipstartrows=0, skipendrows=0, selection='Adj Close', outputcol='Daily Growth'):
    """ 
    reusable for any column

    Parameters
    --
    skipstartrows : int
        Rows to skip at beginning in addition to the 1 row that must be skipped
        because the calculation relies on a prior data point.
    
    Returns
    --
    DataFrame
    """
    size = len(eqdata.index)
    growthdata = eqdata.loc[:, selection].values[(skipstartrows + 1):(size - skipendrows)] / \
            eqdata.loc[:, selection].values[skipstartrows:(-1 - skipendrows)]
    growthindex = eqdata.index[(skipstartrows + 1):(size - skipendrows)]
    return pd.DataFrame(data=growthdata, index=growthindex,
            columns=[outputcol], dtype='float64')

def _get_ratio_to_ave(eqdata, skipstartrows=0, skipendrows=0, ave_interval=252, 
        selection='Volume', outputcol='Rel Vol'):
    """ 
    reusable for any column

    Parameters
    --
    skipstartrows : int, default 0
        Rows to skip at beginning in addition to the `ave_interval` rows that
        must be skipped to get the baseline volume.

    ave_interval : int, default 252
        interval over which to take the average. Defaults to 252 because that
        is normally the number of sesssions in a year.
    
    Returns
    --
    DataFrame
    """
    datalen = len(eqdata.index)
    tmpdata = pn.data.featurize(eqdata, ave_interval, selection=selection)
    averages = tmpdata.mean(axis=1)
    avelen = len(averages.index)
    result_data = eqdata.loc[:, selection].values[(skipstartrows + ave_interval):(datalen - skipendrows)] / \
            averages.values[skipstartrows:(avelen - skipendrows - 1)]
    result_index = eqdata.index[(skipstartrows + ave_interval):(datalen - skipendrows)]
    return pd.DataFrame(data=result_data, index=result_index, columns=[outputcol], dtype='float64')

def get_partitioned_data(features, labels, partition, ix):
    """ separate training and test data using `partition` and `ix` """
    mask = (partition != ix)
    feattrain = features[mask, :]
    _, means = pn.data.center(feattrain[:, 1:], out=feattrain[:, 1:])
    _, stds = pn.data.normalize(feattrain[:, 1:], out=feattrain[:, 1:])
    labtrain = labels[mask, :]
    feattest = features[~mask, :]
    feattest[:, 1:] = feattest[:, 1:] - means
    feattest[:, 1:] = feattest[:, 1:] / stds
    labtest = labels[~mask, :]
    return feattrain, labtrain, feattest, labtest

def _update_hilo(report_errors, error):
    if report_errors.highest < error:
        report_errors.highest = error
    if report_errors.lowest > error:
        report_errors.lowest = error

def evaluate_model(features, labels, partition):
    results = ErrorSummary()
    modein_tot = modeout_tot = 0.
    for i in range(10):
        feattrain, labtrain, feattest, labtest = get_partitioned_data(features, labels, partition, i)
        # get results for model
        print('.', end="")
        sys.stdout.flush()
        model = pl.linreg.get_model(feattrain, labtrain)
        predtrain = pl.linreg.predict(feattrain, model)
        ein = float(pl.error.meansq(predtrain, labtrain))
        modein_tot += ein
        _update_hilo(results.model.ein, ein)
        predtest = pl.linreg.predict(feattest, model)
        eout = float(pl.error.meansq(predtest, labtest))
        modeout_tot += eout
        _update_hilo(results.model.eout, eout)
    # update averages
    results.model.ein.average = modein_tot / 10.0
    results.model.eout.average = modeout_tot / 10.0
    print('.')
    sys.stdout.flush()
    return results 

def print_results(results):
    fname = "RESULTS.md"
    content = """\
Error Summary
==
<table>
<tr>
    <th>Metric</th>
    <th>Average</th>
    <th>Highest</th>
    <th>Lowest</th>
</tr>
<tr>
    <td>Model Eout</td>
    <td>{0}</td>
    <td>{1}</td>
    <td>{2}</td>
</tr>
<tr>
    <td>Model Ein</td>
    <td>{3}</td>
    <td>{4}</td>
    <td>{5}</td>
</tr>
</table>""".format(results.model.eout.average,
        results.model.eout.highest,
        results.model.eout.lowest,
        results.model.ein.average,
        results.model.ein.highest,
        results.model.ein.lowest)
    with open(fname, 'w') as f:
        f.write(content)

def run():
    print("Retrieving data")
    features, labels = get_alldata()
    pfile = "../{0}/partition.csv".format(settings.DATA_ROOT)
    partition = data.partition(pfile, features.shape[0])
    print("Evaluating model")
    results = evaluate_model(features, labels, partition)
    return results

if __name__ == "__main__":
    results = run()
    print_results(results)
