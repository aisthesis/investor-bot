"""
predictors/linreg/store/constants.py

Constants for storing linear regression results.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.
"""
START = '1993'
END = '2016'
N_FEAT_SESS = 256
PRICE_COL = 'Adj Close'
# the following numbers represent the powers of 2 to be used--
# i.e., 2**5 to 2**9 (32, 64, 128, 256, 512)
# end is one past the last value used
PRED_RANGE_BEGIN = 5
PRED_RANGE_END = 10

# path is relative to root of repo
DATA_PATH = 'data/sp500'

# db
DB_NAME = 'invbot01'
DB_COLLECTION = 'lrpred'
