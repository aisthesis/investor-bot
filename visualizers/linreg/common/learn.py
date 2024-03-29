"""
Apply linear regression to data.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import numpy as np
import pynance as pn

def preprocess(features, **kwargs):
    has_means = bool('means' in kwargs)
    has_sd_adj = bool('sd_adj' in kwargs)
    if has_means ^ has_sd_adj:
        raise ValueError('both or neither of means and sd_adj required')
    if has_means and has_sd_adj:
        means = kwargs['means']
        sd_adj = kwargs['sd_adj']
        features[:, 1:] -= means
        features[:, 1:] *= 1. / sd_adj
        return means, sd_adj
    _, means = pn.data.center(features[:, 1:], out=features[:, 1:])
    _, sd_adj = pn.data.normalize(features[:, 1:], out=features[:, 1:])
    return means, sd_adj

def get_model(features, labels):
    return np.linalg.lstsq(features.transpose().dot(features),
            features.transpose().dot(labels))[0]

def get_baseline(features, labels):
    n_cols = 1
    if len(labels.shape) > 1:
        n_cols = labels.shape[1]
    model = np.zeros((features.shape[1], n_cols))
    model[0, :] = np.average(labels, axis=0)
    return model
