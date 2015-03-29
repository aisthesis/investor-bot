"""
Linear regression 23: Duplicate linreg/20 using PCA with various
compression levels.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

from __future__ import print_function
import argparse
from functools import partial
import math
import os
import sys

import numpy as np
import pandas as pd
import pynance as pn
# svd can be faster than the numpy version
from scipy import linalg

sys.path.append('../')
import settings
sys.path.append('../common')
import data
import report

sys.path.append('../../lib')
import pylearn as pl

# global variables
_predexp_begin = 3
_predexp_end = 8
_compexp_begin = 1
_compexp_end = 11
_pred_periods = [2**i for i in range(_predexp_begin, _predexp_end)]
_compressions = None

def get_alldata():
    """ Return features, labels combined for all equities """
    n_feat_sess = 256
    fname = "../{0}/features/lngrowth/sma20/sma50/ema20/ema50/risk20/{1}/labels/multi/{2}/{3}/combined.npy".format(settings.DATA_ROOT,
            n_feat_sess, _predexp_begin, _predexp_end)
    # retrieve from file if it exists
    if os.path.isfile(fname):
        return data.load(fname, _predexp_end - _predexp_begin)
    # otherwise build and save to file
    eqfile = "../{0}/equities.csv".format(settings.DATA_ROOT)
    pricecol = 'Adj Close'
    startdate = '1995-01-01'
    enddate = '2015-01-01'
    _featfuncs, _skipatstart = _get_featfuncs(pricecol)
    featurefn = pn.decorate(partial(pn.data.feat.fromfuncs, _featfuncs, n_feat_sess, skipatstart=_skipatstart),
            _skipatstart + n_feat_sess - 1)
    labelfn = partial(data.multi_period_growth, _predexp_end - _predexp_begin, pricecol, range_begin=_predexp_begin)
    equities = data.get_equities(eqfile)
    directory = os.path.dirname(fname)
    if not os.path.exists(directory):
        os.makedirs(directory)
    features, labels = data.aggregate(equities, startdate, enddate, featurefn, labelfn) 
    data.save(fname, features, labels)
    return features, labels

def _get_toydata():
    _n_rows = 512
    _n_featcols = 40
    _features = np.random.random((_n_rows, _n_featcols))
    _features[:, 0] = 1.
    _labels = np.random.random((_n_rows, _predexp_end - _predexp_begin))
    return _features, _labels

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

def _centerandnormalize(feattrain, feattest):
    """
    Passed to `pl.assess.multi_xval()` as preprocessfn
    """
    _, _means = pn.data.center(feattrain[:, 1:], out=feattrain[:, 1:])
    _, _sd_adj = pn.data.normalize(feattrain[:, 1:], out=feattrain[:, 1:])
    feattest[:, 1:] -= _means
    feattest[:, 1:] *= 1. / _sd_adj
    return feattrain, feattest

def _get_comp_rangemax(release):
    return 9 if release else 6

def _get_empty_res_list():
    _metrics = ('Eout', 'Ein')
    _results = []
    _row = []
    for _comp in _compressions:
        for _pred_period in _pred_periods:
            for _metric in _metrics:
                _results.append([_metric, _pred_period, _comp, 0., 0., 1.])
    return _results

def _get_result_ix(ein, pred_period, compression):
    _comp_ix = int(round(math.log(compression, 2))) - _compexp_begin
    _period_ix = int(round(math.log(pred_period, 2))) - _predexp_begin
    return 2 * (_predexp_end - _predexp_begin) * _comp_ix + 2 * _period_ix + ein

def _update_results(results, ein, eout, compression):
    for i in range(len(ein)):
        _ein_ix = _get_result_ix(1, 2**(_predexp_begin + i), compression)
        _eout_ix = _get_result_ix(0, 2**(_predexp_begin + i), compression)
        # contributions to average
        results[_ein_ix][3] += 0.1 * ein[i]
        results[_eout_ix][3] += 0.1 * eout[i]
        # highs and lows
        _update_hi(results[_ein_ix], 4, ein[i])
        _update_hi(results[_eout_ix], 4, eout[i])
        _update_lo(results[_ein_ix], 5, ein[i])
        _update_lo(results[_eout_ix], 5, eout[i])

def _update_hi(row, index, value):
    if row[index] < value:
        row[index] = value

def _update_lo(row, index, value):
    if row[index] > value:
        row[index] = value

def get_results(features, labels, n_parts, partition, modelfn, errorfn):
    _results = _get_empty_res_list()
    # allocate memory for these upfront to save time
    _ftrain_compressed = np.empty((features.shape[0], _compressions[-1] + 1))
    _ftest_compressed = np.empty((features.shape[0] // 5, _compressions[-1] + 1))
    _ftrain_compressed[:, 0] = 1.
    _ftest_compressed[:, 0] = 1.
    for i in range(n_parts):
        _feattrain, _labtrain, _feattest, _labtest = pl.assess._get_partitioned_data(features, 
                labels, partition, i, _centerandnormalize)
        print('.', end="")
        sys.stdout.flush()
        _lsing, _gamma, _rsingt = linalg.svd(_feattrain[:, 1:], full_matrices=False)
        _rsing = _rsingt.transpose()
        print('.', end="")
        sys.stdout.flush()
        # reduce view to appropriate rows
        _ftrain = _ftrain_compressed[:_feattrain.shape[0], :]
        _ftest = _ftest_compressed[:_feattest.shape[0], :]
        _ftrain[:, 1:]  = _feattrain[:, 1:].dot(_rsing[:, :_compressions[-1]])
        _ftest[:, 1:] = _feattest[:, 1:].dot(_rsing[:, :_compressions[-1]])
        for _compression in _compressions:
            print('.', end="")
            sys.stdout.flush()
            _model = modelfn(_ftrain[:, :_compression + 1], _labtrain)
            _predtrain = _model.predict(_ftrain[:, :_compression + 1])
            _ein = errorfn(_predtrain, _labtrain).flatten()
            _predtest = _model.predict(_ftest[:, :_compression + 1])
            _eout = errorfn(_predtest, _labtest).flatten()
            _update_results(_results, _ein, _eout, _compression)
    print('.')
    sys.stdout.flush()
    return _results

def save_results(results, release=False):
    if release:
        _fname = "RESULTS.md"
    else:
        _fname = "DUMMY.md"
    _contents = []
    _contents.append("Error Metrics")
    _contents.append("==")
    _header_cells = ["Metric", "Forecast Distance", "Components", "Average", "High", "Low"]
    _fmt = ['', ':d', ':d', ':6.4f', ':6.4f', ':6.4f']
    _contents.append(report.make_tbl(_header_cells, results, _fmt))
    _content = "\n".join(_contents)
    with open(_fname, 'w') as f:
        f.write(_content)

def run(release=False):
    print("Retrieving data")
    if release:
        _features, _labels = get_alldata()
    else:
        _features, _labels = _get_toydata()
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
    _n_components = [2**i for i in range(1, _get_comp_rangemax(release))]
    print("Evaluating model")
    _results = get_results(_features, _labels, _n_parts, _partition, _modelfn, _errorfn)
    save_results(_results, release)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-r", "--release", help="run program on real data", action="store_true")
    args = parser.parse_args()
    _release = args.release
    if not _release:
        print("Testing code using toy data")
        _compexp_end = 6
    _compressions = [2**i for i in range(_compexp_begin, _compexp_end)]
    results = run(_release)
