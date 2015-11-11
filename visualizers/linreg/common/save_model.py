"""
Save linear regression model and preprocessing parameters.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import numpy as np

import constants
import data
import learn

def run():
    outfile = constants.MODEL_FILE
    equities = constants.DOW_LEARN
    print('Getting features and labels')
    features, labels = data.labeled_features(equities)
    print('Getting model and preprocessing data')
    model, means, sd_adj = learn.get_model(features, labels)
    print('Saving model and preprocessing data')
    np.savez(outfile, model=model, means=means, sd_adj=sd_adj)
    print('Model and preprocessing data saved as {}'.format(outfile))

if __name__ == '__main__':
    run()
