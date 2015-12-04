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

import os
import traceback

from pymongo import MongoClient
from pymongo.errors import BulkWriteError

import constants
import pred_data

def _tolist(equity, predictions):
    colnames = predictions.columns.tolist()
    return [_todict(equity, rowtimestamp, predictions.loc[rowtimestamp, :], colnames)
            for rowtimestamp in predictions.index]

def _todict(equity, rowtimestamp, row, colnames):
    datekeys = ('Year', 'Month', 'Day')
    ret = {'Equity': equity.upper()}
    ret['Year'] = rowtimestamp.year
    ret['Month'] = rowtimestamp.month
    ret['Day'] = rowtimestamp.day
    for colname in colnames:
        ret[colname] = row.loc[colname]
    return ret

def _get_equities():
    cwd = os.path.dirname(os.path.realpath(__file__))
    proj_root = os.path.normpath(os.path.join(cwd, '../../..'))
    path = os.path.join(proj_root, constants.DATA_PATH)
    eqfile = os.path.join(path, 'oos02.csv')
    return [line.strip() for line in open(eqfile)]

def insert(bulk, equity, predictions):
    entries = _tolist(equity, predictions)
    for entry in entries:
        bulk.insert(entry)
    try:
        result = bulk.execute()
    except BulkWriteError as e:
        print("error writing predictions for '{}'".format(equity))
        print("{} records inserted for '{}'".format(e.details['nInserted'], equity))
    else:
        print("{} records inserted for '{}'".format(result['nInserted'], equity))
    
def run():
    equities = _get_equities()
    client = MongoClient()
    print('db connection opened')
    db = client[constants.DB_NAME]
    coll = db[constants.DB_COLLECTION]
    try:
        for equity in equities:
            if coll.find_one({'Equity': equity}):
                print("'{}' already present and will not be inserted".format(equity))
                continue
            print("getting predictions for '{}'".format(equity))
            try:
                predictions = pred_data.get(equity, constants.START, constants.END)
            except (IOError, ValueError):
                traceback.print_exc()
                print("no predictions to insert for '{}'".format(equity))
                continue
            print("{} predictions retrieved for '{}'".format(predictions.shape[0], equity))
            bulk = coll.initialize_unordered_bulk_op()
            insert(bulk, equity, predictions)
    finally:
        client.close()
        print('db connection closed')
