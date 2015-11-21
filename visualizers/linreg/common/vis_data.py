"""
Generate a dataset for visualiztion
Get predicted labels.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

from functools import partial

import numpy as np
import pandas as pd
import pynance as pn

import constants
import predict

def _get_featfuncs():
    pricecol = constants.PRICE_COL
    ma_wins = (20, 50)
    vol_win = 20
    skipatstart = 50
    funcs = []
    # Growth 
    funcs.append(pn.decorate(partial(pn.tech.growth, selection=pricecol), title='Growth'))
    # ln(growth)
    funcs.append(pn.decorate(partial(pn.tech.ln_growth, selection=pricecol), title='LnGrowth'))
    # SMA 20 growth is proportional to growth over 20 days (factor of 1/20)
    # and the factor disappears when we center and normalize
    # so this technique avoids unnecessary recalculation.
    for ma_win in ma_wins:
        # SMA
        funcs.append(pn.decorate(partial(pn.tech.growth, selection=pricecol, n_sessions=ma_win), 
                title=('SMAGrowth' + str(ma_win))))
        # EMA
        funcs.append(pn.decorate(partial(pn.tech.ema_growth, selection=pricecol, n_sessions=ma_win), 
                title=('EMAGrowth' + str(ma_win))))
    # Growth Risk
    funcs.append(pn.decorate(partial(pn.tech.growth_volatility, window=vol_win, 
            selection=pricecol), title=('GrowthRisk' + str(vol_win))))
    return funcs, skipatstart

def _concat(strval, intval):
    return strval + str(intval)

def get_features(eqdata, n_feat_sess):
    featfuncs, skipatstart = _get_featfuncs()
    allfeatfunc = pn.decorate(partial(pn.data.feat.fromfuncs, featfuncs, n_feat_sess, skipatstart=skipatstart),
            skipatstart + n_feat_sess - 1)
    return allfeatfunc(eqdata)

def get_predictions(modelfile, features):
    model = np.load(modelfile)
    predictions = {}
    predictions['baseline'] = predict.baseline(features.values, model['baseline_model'])
    predictions['linreg']  = predict.linreg(features.values, model['linreg_model'],
            model['means'], model['sd_adj'])
    return predictions

def _combine(eqdata, predictions, n_feat_sess, skipatstart):
    pricecol = constants.PRICE_COL
    pricedata = eqdata.iloc[skipatstart:, :].loc[:, pricecol]
    n_rows = pricedata.shape[0]
    columns = ['Price']
    distances = [2**i for i in range(constants.PRED_RANGE_BEGIN, constants.PRED_RANGE_END)]
    columns += map(partial(_concat, 'Ave Growth '), distances) 
    columns += map(partial(_concat, 'Pred Growth '), distances) 
    columns += map(partial(_concat, 'Ave Price '), distances) 
    columns += map(partial(_concat, 'Pred Price '), distances) 
    combined_data = pd.DataFrame(index=pricedata.index, columns=columns)
    combined_data.loc[:, 'Price'] = pricedata.values
    n_pred_intervals = constants.PRED_RANGE_END - constants.PRED_RANGE_BEGIN
    combined_data.iloc[:, 1:(n_pred_intervals + 1)] = predictions['baseline'] 
    combined_data.iloc[:, (n_pred_intervals + 1):(2 * n_pred_intervals + 1)] = predictions['linreg']
    for i in range(n_pred_intervals):
        distance = 2**(i + constants.PRED_RANGE_BEGIN)
        if distance >= n_rows:
            print('no actual prices for distances over {}'.format(distance))
            break
        # baseline
        prices = predictions['baseline'][:, i] * pricedata.values
        combined_data.iloc[distance:, (2 * n_pred_intervals + 1 + i)] = prices[:n_rows - distance]
        # linreg
        prices = predictions['linreg'][:, i] * pricedata.values
        combined_data.iloc[distance:, (3 * n_pred_intervals + 1 + i)] = prices[:n_rows - distance]
    return combined_data

def get(modelfile, equity, start, end):
    n_feat_sess = constants.N_FEAT_SESS
    eqdata = pn.data.get(equity, start, end)
    features, skipatstart = get_features(eqdata, n_feat_sess)
    predictions = get_predictions(modelfile, features)
    return _combine(eqdata, predictions, n_feat_sess, skipatstart)
