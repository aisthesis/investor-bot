"""
Unit tests for baseline linear regression

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import unittest

import numpy as np
import pandas as pd

import baseline

class TestBaseline(unittest.TestCase):

    def setUp(self):
        self.index = ["2014-01-01", "2014-01-02", "2014-01-03"]
        cols = ['Constant', '-2', '-1', '0']
        d = np.random.random((3, 4))
        d[:, 0] = 1.0
        self.features = pd.DataFrame(data=d, index=self.index, columns=cols) 

    def test_learn_label_vector(self):
        cols = ['Label']
        content = np.arange(1, 2.5, 0.5)
        labels = pd.DataFrame(data=content, index=self.index, columns=cols)
        weights = baseline.learn(self.features, labels)
        self.assertAlmostEqual(weights[0], 1.5)
        for i in range(1, self.features.shape[1]):
            self.assertAlmostEqual(weights[i], 0)

    def test_learn_label_matrix(self):
        cols = ['Label1', 'Label2']
        content = np.arange(1, 4, 0.5).reshape((3, 2))
        labels = pd.DataFrame(data=content, index=self.index, columns=cols)
        weights = baseline.learn(self.features, labels)
        self.assertAlmostEqual(weights[0, 0], 2.0)
        self.assertAlmostEqual(weights[0, 1], 2.5)
        for i in range(1, self.features.shape[1]):
            self.assertAlmostEqual(weights[i, 0], 0)
            self.assertAlmostEqual(weights[i, 1], 0)

if __name__ == '__main__':
    unittest.main()
