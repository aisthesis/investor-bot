"""
predictors/linreg/store/save_preds.py

Save predictions to mongo

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import pymongo

import constants

def _tolist(equity, predictions):
    colnames = predictions.columns.tolist()
    return [_todict(equity, rowtimestamp, predictions.loc[rowtimestamp, :], colnames)
            for rowtimestamp in predictions.index]

def _todict(equity, rowtimestamp, row, colnames):
    datekeys = ('Year', 'Month', 'Day')
    ret = {'Equity': equity}
    ret['Year'] = rowtimestamp.year
    ret['Month'] = rowtimestamp.month
    ret['Day'] = rowtimestamp.day
    for colname in colnames:
        ret[colname] = row.loc[colname]
    return ret

def insert(equity, predictions):
    return _tolist(equity, predictions)
    
