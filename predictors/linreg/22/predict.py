"""
Linear regression 21: PCA preparation

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
# the scipy version is often faster for svd
from scipy import linalg

sys.path.append('../')
import settings
sys.path.append('../common')
import data

def get_alldata(predrange_begin, predrange_end):
    """ Return features, labels combined for all equities """
    n_feat_sess = 256
    fname = "../{0}/features/lngrowth/sma20/sma50/ema20/ema50/risk20/{1}/labels/multi/{2}/{3}/combined.npy".format(settings.DATA_ROOT,
            n_feat_sess, predrange_begin, predrange_end)
    # retrieve from file if it exists
    if os.path.isfile(fname):
        return data.load(fname, predrange_end - predrange_begin)
    # otherwise build and save to file
    eqfile = "../{0}/equities.csv".format(settings.DATA_ROOT)
    pricecol = 'Adj Close'
    startdate = '1995-01-01'
    enddate = '2015-01-01'
    _featfuncs, _skipatstart = _get_featfuncs(pricecol)
    featurefn = pn.decorate(partial(pn.data.feat.fromfuncs, _featfuncs, n_feat_sess, skipatstart=_skipatstart),
            _skipatstart + n_feat_sess - 1)
    labelfn = partial(data.multi_period_growth, predrange_end - predrange_begin, pricecol, range_begin=predrange_begin)
    equities = data.get_equities(eqfile)
    directory = os.path.dirname(fname)
    if not os.path.exists(directory):
        os.makedirs(directory)
    features, labels = data.aggregate(equities, startdate, enddate, featurefn, labelfn) 
    data.save(fname, features, labels)
    return features, labels

def _get_featfuncs(pricecol):
    _ma_wins = (20, 50)
    _vol_win = 20
    _skipatstart = 50
    _funcs = []
    # Growth 
    _funcs.append(pn.decorate(partial(pn.tech.growth, selection=pricecol), title='Growth'))
    # ln(growth)
    _funcs.append(pn.decorate(partial(pn.tech.ln_growth, selection=pricecol), title='LnGrowth'))
    # SMA 20 growth is proportional to growth over 20 days (factor of 1/20)
    # and the factor disappears when we center and normalize
    # so this technique avoids unnecessary recalculation.
    for _ma_win in _ma_wins:
        # SMA
        _funcs.append(pn.decorate(partial(pn.tech.growth, selection=pricecol, n_sessions=_ma_win), 
                title=('SMAGrowth' + str(_ma_win))))
        # EMA
        _funcs.append(pn.decorate(partial(pn.tech.ema_growth, selection=pricecol, n_sessions=_ma_win), 
                title=('EMAGrowth' + str(_ma_win))))
    # Growth Risk
    _funcs.append(pn.decorate(partial(pn.tech.growth_volatility, window=_vol_win, 
            selection=pricecol), title=('GrowthRisk' + str(_vol_win))))
    return _funcs, _skipatstart

def _preprocess(features):
    _features = features[:, 1:]
    _, _means = pn.data.center(_features, out=_features)
    _, _sd_adj = pn.data.normalize(_features, out=_features)
    return _features

def save_results(rec_errs): 
    print("Saving reconstruction errors")
    fname = "results.csv"
    _to_save = np.empty((len(rec_errs), 2))
    _to_save[:, 0] = np.arange(len(rec_errs))
    _to_save[:, 1] = rec_errs
    _header = 'Components,Reconstruction Error'
    np.savetxt(fname, _to_save, delimiter=',', header=_header, comments='', fmt=['%d', '%6.4f'])

def get_features():
    _predrange_begin = 3
    _predrange_end = 8
    print("Retrieving data")
    _rawfeat, _ = get_alldata(_predrange_begin, _predrange_end)
    print("Verifying data integrity")
    if pn.has_na(_rawfeat):
        raise ValueError("features contain missing data")
    print("Features validated")
    print("Remove const, center, normalize")
    _features = _preprocess(_rawfeat)
    return _features

def get_eigenvalues(features):
    print("Performing single value decomposition")
    print("Please wait at least 5 minutes for results")
    sys.stdout.flush()
    u, s, v = linalg.svd(features, full_matrices=False)
    print("Single value decomposition complete")
    return s

def get_reconstruction_errs(sing_vals):
    _rec_errors = np.empty((len(sing_vals),))
    _sing_vals_sq = sing_vals * sing_vals
    _sum_of_squares = np.sum(_sing_vals_sq)
    _remaining = _sum_of_squares
    for i in range(len(_rec_errors)):
        _rec_errors[i] = _remaining / _sum_of_squares
        _remaining -= _sing_vals_sq[i]
    return _rec_errors

def run():
    _feat = get_features()
    _sing_vals = get_eigenvalues(_feat)
    _rec_errs = get_reconstruction_errs(_sing_vals)
    save_results(_rec_errs)
    return _rec_errs


if __name__ == "__main__":
    run()
