"""
Abstract base class for learned models.

Copyright (c) 2015- Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

class Model(object):
    """
    Abstract base class for machine learning models, which must
    implement a constructor and a `predict()` method.
    """
    def __init__(self, **kwargs):
        raise NotImplementedError("Subclasses must implement constructor")

    def predict(self, features):
        raise NotImplementedError("Subclasses must implement predict()")
