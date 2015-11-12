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

import os

import numpy as np

import constants
import data
import predict
import report

def stderr(predicted, actual):
    diff = predicted - actual
    return np.sqrt(np.average(diff * diff, axis=0).reshape(1, diff.shape[1]))

def run(equities, outfile):
    if os.path.isfile(outfile):
        print("File '{}' exists. Delete to rebuild.".format(outfile))
        return
    modelfile = constants.MODEL_FILE
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
    print('Writing summary')
    distances = [2**i for i in range(constants.PRED_RANGE_BEGIN, constants.PRED_RANGE_END)]
    err_summary = report.errorsbydistance(baseline_err.flatten(), linreg_err.flatten(),
            distances, 'Linear Regression')
    with open(outfile, 'w') as f:
        f.write(err_summary)
    print('Error summary written to file {}'.format(outfile))
    
if __name__ == '__main__':
    print('Getting in-sample error summary')
    run(constants.DOW_LEARN, 'IN_SAMPLE.md')
    print('Getting out-of-sample error summary')
    run(constants.DOW_TEST, 'OUT_OF_SAMPLE.md')
