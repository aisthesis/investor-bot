"""
Select equities for learning and training.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import random

def sample(equities, n_train, n_test):
    """
    Return random selection of equities for training and testing

    Usage
    -----
    eqtrain, eqtest = eq_sel.sample(equities, 64, 32)
    """
    if n_train + n_test > len(equities):
        raise ValueError('insufficient number of equities')
    # make a copy of equities so as not to modify input
    _eqs = equities[:]
    random.shuffle(_eqs)
    return _eqs[:n_train], _eqs[-n_test:]
