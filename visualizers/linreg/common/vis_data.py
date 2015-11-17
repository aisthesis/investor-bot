"""
Generate a dataset for visualiztion
Get predicted labels.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import pynance as pn

def get(equity, start, end):
    eqdata = pn.data.get(equity, start, end)
    return None
