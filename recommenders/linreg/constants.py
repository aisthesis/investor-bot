"""
recommenders/linreg/constants.py

Constants for recommendations based on linear regression results.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.
"""

LOGFMT = "%(asctime)s %(levelname)s %(module)s.%(funcName)s : %(message)s"
# the following numbers represent the powers of 2 to be used--
# i.e., 2**5 to 2**9 (32, 64, 128, 256, 512)
# end is one past the last value used
PRED_RANGE_BEGIN = 5
PRED_RANGE_END = 10
