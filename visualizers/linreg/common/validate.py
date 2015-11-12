"""
Validate linear regression model.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com

Validation consists of running the model on test data (the
Dow equities not used for learning) and verifying that the
linear regression model improves on the baseline, as was
the case in `predictors/linreg/24`.
"""

import numpy as np

import constants
import data
import predict

def stderr(predicted, actual):
    diff = predicted - actual
    return np.sqrt(np.average(diff * diff, axis=0).reshape(1, diff.shape[1]))

def run():
    equities = constants.DOW_TEST
    modelfile = constants.MODEL_FILE
    #FIXME
    equities = ['ge', 'cat']
    print('Getting features and labels')
    features, labels = data.labeled_features(equities)
    print('Getting models and preprocessing data')
    models = np.load(modelfile) 
    baseline_model = models['baseline_model']
    linreg_model = models['linreg_model']
    means = models['means']
    sd_adj = models['sd_adj']
    print('Getting predictions')
    baseline_pred = predict.baseline(features, baseline_model)
    linreg_pred = predict.linreg(features, linreg_model, means, sd_adj)
    print('Getting standard errors')
    baseline_err = stderr(baseline_pred, labels)
    linreg_err = stderr(linreg_pred, labels)
    print('baseline err:')
    print(baseline_err)
    print('linreg err:')
    print(linreg_err)
    
if __name__ == '__main__':
    run()
