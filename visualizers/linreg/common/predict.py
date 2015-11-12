"""
Get predicted labels.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import numpy as np

import learn

def linreg(features, model, means, sd_adj):
    learn.preprocess(features, means=means, sd_adj=sd_adj)
    return features.dot(model)

def baseline(features, model):
    return features.dot(model)
