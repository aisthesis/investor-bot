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

def save_results(results, predrange_begin, predrange_end):
    fname = "RESULTS.md"
    content = report.errors_by_dist(results, [2**i for i in range(predrange_begin, predrange_end)])
    with open(fname, 'w') as f:
        f.write(content)

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

if __name__ == "__main__":
    """
    Output:
    (array([   0,    1,    5,    6,    7,    8,   10,   11,   16,   18,   19,
    24,  271,  273,  275,  277,  279,  282,  287,  290,  291,  321,
    1530, 1531, 1532, 1533, 1534, 1535, 1536, 1784, 1786, 1787, 1788,
    1789, 1790]),)
    [  2.44600856e+03   2.01158460e+03   1.71470941e+03   1.59312944e+03
    1.49028708e+03   1.24434748e+03   1.07122034e+03   9.98881821e+02
    8.20380777e+02   7.45999847e+02   6.89718333e+02   5.80941533e+02
    2.35913080e+02   2.12415979e+02   1.87038707e+02   1.63841538e+02
    1.42888494e+02   1.27170418e+02   1.11077295e+02   1.01152283e+02
    9.51299879e+01   5.31507824e+01   1.21680558e+00   9.86042893e-01
    6.52528716e-01   5.63440700e-01   4.56547579e-01   2.35028855e-01
    3.38407908e-13   1.68018061e-13   1.53701252e-14   9.01075619e-15
    7.74860119e-15   6.33784055e-15   3.62561954e-15]
    """
    _feat = get_features()
    _s = get_eigenvalues(_feat)
    _decay = _s[:-1] / _s[1:]
    print((_decay > 1.05).nonzero())
    print(_s[_decay > 1.05])
