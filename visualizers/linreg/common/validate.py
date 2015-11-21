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

def run(equities, modelfile, outfile):
    if os.path.isfile(outfile):
        print("File '{}' exists. Delete to rebuild.".format(outfile))
        return
    print('Getting features and labels')
    features, labels = data.labeled_features(equities, constants.START, constants.END)
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
    cwd = os.path.dirname(os.path.realpath(__file__))
    # Dow
    print('Processing Dow selection')
    path = os.path.normpath(os.path.join(cwd, constants.DOW['path']))
    equities = constants.DOW['learn']
    modelfile = os.path.join(path, constants.MODEL_FILE)
    outfile = os.path.join(path, 'IN_SAMPLE.md')
    print('Getting Dow in-sample error summary')
    run(equities, modelfile, outfile)
    print('Getting Dow out-of-sample error summary')
    equities = constants.DOW['test']
    outfile = os.path.join(path, 'OUT_OF_SAMPLE.md')
    run(equities, modelfile, outfile)
    # S&P 500
    print('Processing selections from S&P')
    path = os.path.normpath(os.path.join(cwd, '../sp500'))
    sizes = constants.SP500_SIZES
    ofnames = constants.SUMMARY_FILES
    for i in range(len(sizes)):
        modelfile = os.path.join(path, constants.MODEL_FILE_TEMPLATE.format(i))
        for name in ('train', 'test'):
            print('Generating summary for {}{:02d} on S&P'.format(name, i))
            eqfile = os.path.join(path, '{}{:02d}.csv'.format(name, i))
            equities = [line.strip() for line in open(eqfile)]
            outfile = os.path.join(path, '{}{:02d}.md'.format(ofnames[name], i))
            run(equities, modelfile, outfile)

            
