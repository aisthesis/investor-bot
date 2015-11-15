"""
Get relevant contents from text files.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import csv

def get_sp500(fname):
    """
    Return a list of S&P equities from '../sp500/constituents.csv'
    """
    equities = []
    with open(fname) as infile:
        reader = csv.reader(infile)
        # skip header row
        reader.next()
        for row in reader:
            equities.append(row[0])
    return equities
