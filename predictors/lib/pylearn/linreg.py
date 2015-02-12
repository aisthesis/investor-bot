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

from .model import Model

class LinRegModel(Model):
    def __init__(self, **kwargs):
        self.weights = kwargs.get('weights')
        if self.weights is None:
            raise TypeError("ctor missing 1 keyword argument: 'weights'")

    def predict(self, features):
        return features.dot(self.weights)

def get_model(features, labels, lamb=0.):
    if isinstance(features, pd.DataFrame):
        _feat = features.values
        _lab = labels.values
    else:
        _feat = features
        _lab = labels
    _n_cols = _feat.shape[1]
    _weights = np.linalg.lstsq(_feat.transpose().dot(_feat)\
            + lamb * np.identity(_n_cols, dtype=np.float64),\
            _feat.transpose().dot(_lab))[0]
    return LinRegModel(weights=_weights)
