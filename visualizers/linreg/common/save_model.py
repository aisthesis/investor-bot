"""
Save linear regression model and preprocessing parameters.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import os

import numpy as np

import constants
import data
import learn

def run(equities, outfile):
    if os.path.isfile(outfile):
        print("File '{}' exists. Delete to rebuild.".format(outfile))
        return
    print('Getting features and labels')
    features, labels = data.labeled_features(equities)
    print('Getting baseline and regression model with preprocessing adjustments')
    baseline_model = learn.get_baseline(features, labels)
    means, sd_adj = learn.preprocess(features)
    linreg_model = learn.get_model(features, labels)
    print('Saving baseline and regression models with preprocessing adjustments')
    np.savez(outfile, baseline_model=baseline_model, linreg_model=linreg_model, 
            means=means, sd_adj=sd_adj)
    print('Models and preprocessing data saved as {}'.format(outfile))

if __name__ == '__main__':
    cwd = os.path.dirname(os.path.realpath(__file__))
    # Dow
    path = os.path.normpath(os.path.join(cwd, constants.DOW['path']))
    outfile = os.path.join(path, constants.MODEL_FILE)
    run(constants.DOW['learn'], outfile)
    # S&P
    path = os.path.normpath(os.path.join(cwd, '../sp500'))
    sizes = constants.SP500_SIZES
    for i in range(len(sizes)):
        eqfile = os.path.join(path, 'train{:02d}.csv'.format(i))
        equities = [line.strip() for line in open(eqfile)]
        outfile = os.path.join(path, constants.MODEL_FILE_TEMPLATE.format(i))
        run(equities, outfile)
