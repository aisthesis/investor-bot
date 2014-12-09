"""
Classes for storing relevant metrics

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

class Errors(object):

    def __init__(self, **kwargs):
        # pessimistic initialization
        self.highest = kwargs.get('highest', 0.)
        self.lowest = kwargs.get('lowest', 1.)
        self.average = kwargs.get('average', None)

class EinEout(object):

    def __init__(self, **kwargs):
        self.ein = kwargs.get('ein', Errors())
        self.eout = kwargs.get('eout', Errors())

class ErrorSummary(object):

    def __init__(self, **kwargs):
        self.baseline = kwargs.get('baseline', EinEout())
        self.model = kwargs.get('model', EinEout())
