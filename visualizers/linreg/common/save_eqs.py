"""
Save equities for learning and training.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import os

import constants
import eq_sel
import file_parser as fp

def write(selected, path, index):
    for name in ('train', 'test'):
        fname = os.path.join(path, '{}{:02d}.csv'.format(name, index))
        if os.path.isfile(fname):
            print("File'{}' exists. No action taken".format(fname))
            return
        print("Writing {} equities to file '{}'".format(len(selected[name]), fname))
        with open(fname, 'w') as f:
            for equity in selected[name]:
                f.write("{}\n".format(equity))

def run():
    cwd = os.path.dirname(os.path.realpath(__file__))
    # S&P 500
    path = os.path.normpath(os.path.join(cwd, '../sp500'))
    if not os.path.isdir(path):
        os.makedirs(path)
    infile = 'constituents.csv'
    equities = fp.get_sp500(os.path.join(path, infile))
    # sizes of training and test data sets
    sizes = constants.SP500_SIZES
    selected = {}
    for i in range(len(sizes)):
        selected['train'], selected['test'] = eq_sel.sample(equities, sizes[i]['train'], sizes[i]['test'])
        write(selected, path, i)

if __name__ == '__main__':
    run()
