"""
recommenders/linreg/recpuller.py

Get recommendations for a list of equities.

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import logging

import pandas as pd
from pymongo import MongoClient

import constants

def from_mongo(dbname, collname, date, equities, preddist):
    logger = _get_logger()
    _check_preddist(logger, preddist)
    qry = _get_query(date)
    ret = []
    client = MongoClient()
    logger.info('db connection opened')
    db = client[dbname]
    coll = db[collname]
    for equity in equities:
        qry['Equity'] = equity
        record = coll.find_one(qry)
        if record:
            ret.append((equity, record[str(preddist)]))
        else:
            logger.warning('no records found for {} on {}'.format(equity, date))
    client.close()
    logger.info('db connection closed')
    return ret

def _get_logger():
    logger = logging.getLogger(__name__)
    if not len(logger.handlers):
        logger.setLevel(logging.DEBUG)
        # TODO dev configurations
        # console handler for debugging
        handler = logging.StreamHandler()
        formatter = logging.Formatter(constants.LOGFMT)
        handler.setFormatter(formatter)
        logger.addHandler(handler)
    return logger

def _get_query(date):
    ts = pd.Timestamp(date)
    return {'Equity': '', 'Year': ts.year, 'Month': ts.month, 'Day': ts.day}

def _check_preddist(logger, preddist):
    if preddist not in [2**i for i in range(constants.PRED_RANGE_BEGIN, 
        constants.PRED_RANGE_END)]:
        msg = '{} is not a valid preddist'.format(preddist)
        logger.error(msg)
        raise ValueError(msg)

