"""
Unit tests for pylearn.error module

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import sys
import unittest

import numpy as np
import pandas as pd

sys.path.append('../')
import error

class TestError(unittest.TestCase):

    def setUp(self):
        self.predicted = np.arange(6.).reshape((2, 3))
        self.actual = np.arange(6., 18., 2.).reshape((2, 3))

    def test_meansq_ndarray(self):
        meansqerr = error.meansq(self.predicted, self.actual)
        self.assertTrue(isinstance(meansqerr, np.ndarray))
        self.assertAlmostEqual(meansqerr[0, 0], 58.5)
        self.assertAlmostEqual(meansqerr[0, 1], 74.5)
        self.assertAlmostEqual(meansqerr[0, 2], 92.5)

    def test_meansq_dframe(self):
        cols = ['One', 'Two', 'Three']
        predicted = pd.DataFrame(data=self.predicted, columns=cols)
        actual = pd.DataFrame(data=self.actual, columns=cols)
        meansqerr = error.meansq(predicted, actual)
        self.assertTrue(isinstance(meansqerr, pd.DataFrame))
        self.assertEqual(meansqerr.columns.tolist(), cols)
        self.assertAlmostEqual(meansqerr.iloc[0, 0], 58.5)
        self.assertAlmostEqual(meansqerr.iloc[0, 1], 74.5)
        self.assertAlmostEqual(meansqerr.iloc[0, 2], 92.5)

if __name__ == '__main__':
    unittest.main()
