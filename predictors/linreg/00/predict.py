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
import os
import sys

import numpy as np

sys.path.append('../')
import settings
sys.path.append('../common')
import baseline
import data
from metrics import ErrorSummary
import pylearn as pl

def get_alldata():
    """ Return features, labels combined for all equities """
    eqfile = "../{0}/equities.csv".format(settings.DATA_ROOT)
    equities = data.get_equities(eqfile)
    n_feat_sess = 256
    prediction_interval = 64
    featurecols = ['Adj Close']
    labelcol = 'Adj Close'
    startdate = '1960-01-01'
    enddate = '2014-12-11'
    fname = "../{0}/features/{1}/labels/real/{2}/combined.npy".format(settings.DATA_ROOT,
            n_feat_sess, prediction_interval) 
    # retrieve from file if it exists
    if os.path.isfile(fname):
        return data.load(fname)
    # otherwise build and save to file
    directory = os.path.dirname(fname)
    if not os.path.exists(directory):
        os.makedirs(directory)
    features, labels = data.build_alldata(equities, n_feat_sess, prediction_interval,
            featurecols, labelcol, startdate, enddate)
    data.save(fname, features, labels)
    return features, labels

def get_partitioned_data(features, labels, partition, ix):
    """ separate training and test data using `partition` and `ix` """
    mask = (partition != ix)
    feattrain = features[mask, :]
    labtrain = labels[mask, :]
    feattest = features[~mask, :]
    labtest = labels[~mask, :]
    return feattrain, labtrain, feattest, labtest

def _update_hilo(report_errors, error):
    if report_errors.highest < error:
        report_errors.highest = error
    if report_errors.lowest > error:
        report_errors.lowest = error

def evaluate_model(features, labels, partition):
    results = ErrorSummary()
    baseein_tot = baseeout_tot = basegrowth_tot = 0.
    for i in range(10):
        feattrain, labtrain, feattest, labtest = get_partitioned_data(features, labels, partition, i)
        # get results for baseline    
        print('.', end="")
        sys.stdout.flush()
        model = baseline.get_model(feattrain, labtrain)
        basegrowth_tot += float(model[0])
        predtrain = baseline.predict(feattrain, model)
        ein = float(pl.error.meansq(predtrain, labtrain))
        baseein_tot += ein
        _update_hilo(results.baseline.ein, ein)
        predtest = baseline.predict(feattest, model)
        eout = float(pl.error.meansq(predtest, labtest))
        baseeout_tot += eout
        _update_hilo(results.baseline.eout, eout)
    # update averages
    results.baseline.ein.average = baseein_tot / 10.0
    results.baseline.eout.average = baseeout_tot / 10.0
    ave_base_growth = basegrowth_tot / 10.0
    print('.')
    sys.stdout.flush()
    return results, ave_base_growth

def print_results(results, baseline_growth):
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
    <td>Baseline Eout</td>
    <td>{0}</td>
    <td>{1}</td>
    <td>{2}</td>
</tr>
<tr>
    <td>Baseline Ein</td>
    <td>{3}</td>
    <td>{4}</td>
    <td>{5}</td>
</tr>
</table>

Average baseline growth: {6}""".format(
        results.baseline.eout.average,
        results.baseline.eout.highest,
        results.baseline.eout.lowest,
        results.baseline.ein.average,
        results.baseline.ein.highest,
        results.baseline.ein.lowest,
        baseline_growth)
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
    print_results(results, baseline_growth)
