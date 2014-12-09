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
    isdataframe = isinstance(predicted, pd.DataFrame)
    if isdataframe:
        diff = predicted.values - actual.values
    else:
        diff = predicted - actual
    content = np.average(diff * diff, axis=0).reshape((1, predicted.shape[1]))
    if not isdataframe:
        # inputs are ndarray
        return content
    # inputs are DataFrame, so return same
    return pd.DataFrame(data=content, index=['Mean Sq Error'], columns=predicted.columns)
