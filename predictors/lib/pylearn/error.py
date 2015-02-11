"""
Error functions for machine learning

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import numpy as np
import pandas as pd

def meansq(predicted, actual):
    """
    Return mean squared error by column of ndarray or DataFrame
    """
    return _wrapper(predicted, actual, _meansq_measure, ['Mean Sq Error'])

def stderr(predicted, actual):
    """
    Return square root of mean squared error
    """
    return _wrapper(predicted, actual, _stderr_measure, ['Std Error'])

def _wrapper(predicted, actual, measure_fn, df_index):
    """
    Wrapper to handle either DataFrame or ndarray as input.
    """
    isdataframe = isinstance(predicted, pd.DataFrame)
    if isdataframe:
        diff = predicted.values - actual.values
    else:
        diff = predicted - actual
    content = measure_fn(diff)
    if not isdataframe:
        # inputs are ndarray
        return content
    # inputs are DataFrame, so return same
    return pd.DataFrame(data=content, index=df_index, columns=predicted.columns)

def _meansq_measure(diff):
    return np.average(diff * diff, axis=0).reshape((1, diff.shape[1]))

def _stderr_measure(diff):
    return np.sqrt(_meansq_measure(diff))
