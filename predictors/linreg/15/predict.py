"""
Linear regression 15: Multiple metrics as features over 256 sessions.

Copyright (c) 2015 Marshall Farrier

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
import pylearn as pl
import report

def get_alldata(n_pred_intervals):
    """ Return features, labels combined for all equities """
    n_feat_sess = 256
    fname = "../{0}/features/lngrowth/relvol/sma20/sma50/ema20/risk20/{1}/labels/multi/{2}/combined.npy".format(settings.DATA_ROOT,
            n_feat_sess, n_pred_intervals) 
    # retrieve from file if it exists
    if os.path.isfile(fname):
        return data.load(fname, n_pred_intervals)
    # otherwise build and save to file
    eqfile = "../{0}/equities.csv".format(settings.DATA_ROOT)
    pricecol = 'Adj Close'
    startdate = '1995-01-01'
    enddate = '2015-01-01'
    _featfuncs, _skipatstart = _get_featfuncs(pricecol)
    featurefn = pn.decorate(partial(pn.data.feat.fromfuncs, _featfuncs, n_feat_sess, skipatstart=_skipatstart),
            _skipatstart + n_feat_sess - 1)
    labelfn = partial(data.multi_period_growth, n_pred_intervals, pricecol)
    equities = data.get_equities(eqfile)
    directory = os.path.dirname(fname)
    if not os.path.exists(directory):
        os.makedirs(directory)
    features, labels = data.aggregate(equities, startdate, enddate, featurefn, labelfn) 
    data.save(fname, features, labels)
    return features, labels

def _get_featfuncs(pricecol):
    _averaging_interval = 252
    _sma_wins = (20, 50)
    _ma_win = 20
    _skipatstart = _averaging_interval
    _funcs = []
    # Growth 
    _funcs.append(pn.decorate(partial(pn.tech.growth, selection=pricecol), title='Growth'))
    # ln(growth)
    _funcs.append(pn.decorate(partial(pn.tech.ln_growth, selection=pricecol), title='LnGrowth'))
    # Relative volume
    _funcs.append(pn.decorate(partial(pn.tech.ratio_to_ave, _averaging_interval),
            title='RelVol'))            
    # SMA 20 growth is proportional to growth over 20 days (factor of 1/20)
    # and the factor disappears when we center and normalize
    # so this technique avoids unnecessary recalculation.
    for _sma_win in _sma_wins:
        _funcs.append(pn.decorate(partial(pn.tech.growth, selection=pricecol, n_sessions=_sma_win), 
                title=('SMAGrowth' + str(_sma_win))))
    # EMA 20
    _funcs.append(pn.decorate(partial(pn.tech.ema_growth, selection=pricecol, n_sessions=_ma_win), 
            title=('EMAGrowth' + str(_ma_win))))
    # Growth volatility, 20 session window
    _funcs.append(pn.decorate(partial(pn.tech.growth_volatility, window=_ma_win, 
            selection=pricecol), title=('GrowthRisk' + str(_ma_win))))
    return _funcs, _skipatstart

def _centerandnormalize(feattrain, feattest):
    """
    Passed to `pl.assess.multi_xval()` as preprocessfn
    """
    _, _means = pn.data.center(feattrain[:, 1:], out=feattrain[:, 1:])
    _, _sd_adj = pn.data.normalize(feattrain[:, 1:], out=feattrain[:, 1:])
    feattest[:, 1:] -= _means
    feattest[:, 1:] *= 1. / _sd_adj
    return feattrain, feattest

def save_results(results, n_pred_intervals):
    fname = "RESULTS.md"
    content = report.errors_by_dist(results, [2**i for i in range(n_pred_intervals)])
    with open(fname, 'w') as f:
        f.write(content)

def run(n_pred_intervals):
    print("Retrieving data")
    _features, _labels = get_alldata(n_pred_intervals)
    print("Verifying data integrity")
    if pn.has_na(_features):
        raise ValueError("features contain missing data")
    if pn.has_na(_labels):
        raise ValueError("labels contain missing data")
    print("Features and labels validated")
    _pfile = "../{0}/partition.csv".format(settings.DATA_ROOT)
    _n_parts = 10
    _partition = data.partition(_pfile, _features.shape[0])
    _modelfn = pl.linreg.get_model
    _errorfn = pl.error.stderr
    print("Evaluating model")
    results = pl.assess.multi_xval(_features, _labels, _n_parts, _partition, 
            _modelfn, _errorfn, _centerandnormalize)
    return results

if __name__ == "__main__":
    # powers of 2 from 0 to 6: 1, 2, 4, 8, 16, 32, 64, 128, 256
    _n_pred_intervals = 9
    results = run(_n_pred_intervals)
    save_results(results, _n_pred_intervals)
