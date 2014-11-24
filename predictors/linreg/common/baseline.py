"""
Baseline linear regression

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import numpy as np

def learn(features, labels):
    """
    baseline for measuring performance of other models

    Only the first row of the returned `weights` matrix (or column vector)
    will be nonzero. The resulting prediction will always
    be just the average of the input labels. weights[0, :]
    will be set to this average.

    If `labels` has multiple columns, the first row of the
    `weights` matrix will represent the average of the corresponding
    column.

    Parameters
    ---
    features : DataFrame
        includes constant feature
    labels : DataFrame
        real values representing the relative value of an equity
        some number of days in the future. For example, if the row
        representing data for 2014-10-01 has as last value 100.00,
        the labels represent prices 64 sessions into the future, and 
        the equity had value 125.00 at the close of that future
        session, then the label would be 1.25. The label
        is expected to be future price divided by current price.

    Return
    ---
    weights : numpy ndarray 
        weights is a vector with the same length as the number of
        columns in the `features` DataFrame. The dot product of features
        and weights provides predictions.
    """
    if len(labels.shape) == 1:
        weights = np.zeros((features.shape[1], 1))
    else:
        weights = np.zeros((features.shape[1], labels.shape[1]))

    weights[0, :] = np.average(labels, axis=0)
    return weights
