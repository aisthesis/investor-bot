"""
Functions for assembling data sets for linear regression

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com

This module assumes the canonical feature set found in `predictors/linreg/24`.
Labels are returns over prediction intervals incrementing from 32 to 512 in
powers of 2. Shorter intervals allow no improvement over the baseline, and longer
intervals seem impractical.
"""

from functools import partial

import numpy as np
import pandas as pd
import pynance as pn

import constants

def _multi_period_growth(n_periods, pricecol, eqdata, range_begin=0):
    """
    Function to be passed using partial to `pn.data.labeledfeatures()`
    """
    _skipatend = 2**(n_periods + range_begin - 1)
    _size = len(eqdata.index)
    _cols = map(str, map(lambda n: 2**n, range(range_begin, range_begin + n_periods)))
    _all_labs = pd.DataFrame(index=eqdata.index[:-_skipatend], columns=_cols, dtype=np.float64)
    for i in range(range_begin, n_periods + range_begin):
        _df = pn.data.lab.growth(2**i, pricecol, eqdata)
        _all_labs.iloc[:, i - range_begin] = _df.iloc[:(_size - _skipatend), 0]
    return _all_labs, _skipatend

def _aggregate(equities, startdate, enddate, featurefunc, labelfunc):
    """
    Aggregate data for all of the given equities
    """
    j = 0
    while j < len(equities):
        _eqdata = pn.data.get(equities[j], startdate, enddate)
        print("{0} records retrieved for equity '{1}'".format(len(_eqdata.index), equities[j]))
        j += 1
        if _insufficient_data(_eqdata):
            print('ignoring equity due to insufficient data')
        else:
            break
    if j >= len(equities):
        raise ValueError('no equities found with sufficient data')

    _featdf, _labdf = pn.data.labeledfeatures(_eqdata, featurefunc, labelfunc)
    _features = _featdf.values
    _labels = _labdf.values
    for i in range(j, len(equities)):
        _eqdata = pn.data.get(equities[i], startdate, enddate)
        print("{0} records retrieved for equity '{1}'".format(len(_eqdata.index), equities[i]))
        if _insufficient_data(_eqdata):
            print('ignoring equity due to insufficient data')
            continue
        _featdf, _labdf = pn.data.labeledfeatures(_eqdata, featurefunc, labelfunc)
        _features = np.append(_features, _featdf.values, axis=0)
        _labels = np.append(_labels, _labdf.values, axis=0)
    return _features, _labels

def _insufficient_data(eqdata):
    min_sessions = constants.N_FEAT_SESS * 12 + 2**(constants.PRED_RANGE_END - 1)
    return eqdata.values.shape[0] <= min_sessions

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

def labeled_features(equities, start, end):
    n_feat_sess = constants.N_FEAT_SESS
    pricecol = constants.PRICE_COL
    predrange_begin = constants.PRED_RANGE_BEGIN
    predrange_end = constants.PRED_RANGE_END
    featfuncs, skipatstart = _get_featfuncs(pricecol)
    featurefn = pn.decorate(partial(pn.data.feat.fromfuncs, featfuncs, n_feat_sess, skipatstart=skipatstart),
            skipatstart + n_feat_sess - 1)
    labelfn = partial(_multi_period_growth, predrange_end - predrange_begin, pricecol, range_begin=predrange_begin)
    return _aggregate(equities, start, end, featurefn, labelfn) 
