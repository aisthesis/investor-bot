"""
Linear regression

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import numpy as np
import pandas as pd

def get_model(features, labels):
    if isinstance(features, pd.DataFrame):
        _feat = features.values
        _lab = labels.values
    else:
        _feat = features
        _lab = labels
    return np.linalg.pinv(_feat).dot(_lab)

def predict(features, model):
    """ Return ndarray of predictions """
    if isinstance(features, pd.DataFrame):
        _feat = features.values
    else:
        _feat = features
    return _feat.dot(model)
