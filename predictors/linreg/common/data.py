"""
Functions for assembling data sets for linear regression

Copyright (c) 2014 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import os

import numpy as np
import pandas as pd
import pynance as pn

def get_equities(fname):
    with open(fname) as f:
        equities = f.read().splitlines()
    return equities

def partition(fname, size, nparts=10):
    """
    Return and, if necessary, save an ndarray of the given size with 
    integer values randomly sampled from [0, nparts).
    If such an array has already been saved to file, the
    contents of the file will be returned as an ndarray. If not,
    a random array of the given size will be generated and saved
    for future use.

    To be used for partitioning data in a random
    yet reproducible manner.
    """
    if os.path.isfile(fname):
        randpart = np.loadtxt(fname, dtype=int)[:size]
        if len(randpart) < size:
            raise ValueError("saved file too small")
    else:
        randpart = np.random.randint(nparts, size=size)
        np.savetxt(fname, randpart, fmt="%d")
    return randpart

def get_eqfeatures(data, n_feat_sess, prediction_interval, data_col, startdate, enddate):
    """
    Return a DataFrame containing the specified features for the given
    data set.
    """
    return pn.data.featurize(data, n_feat_sess, 
            selection=data_col).iloc[:-prediction_interval, :]

def get_eqlabels(data, n_feat_sess, prediction_interval, data_col, startdate, enddate):
    """
    Return a DataFrame containing the specified labels for the given
    data set.
    """
    labeldata = data.loc[:, data_col].values[(n_feat_sess + prediction_interval - 1):] / \
            data.loc[:, data_col].values[(n_feat_sess - 1):-prediction_interval]
    labels = pd.DataFrame(data=labeldata, index=data.index[(n_feat_sess - 1):-prediction_interval],
            columns=['Return Ratio'], dtype='float64')
    return labels

def build_alldata(equities, n_feat_sess, prediction_interval, featurecols, labelcol, startdate, enddate):
    """
    Return an ndarray of features combining the data for all `equities` using the
    given parameters and a vector of labels.

    Features are normalized, and the constant feature is prepended.

    Parameters
    --
    selection : list of strings
        columns to use from DataFrame retrieved for each equity
    """
    features = np.empty((0, n_feat_sess * len(featurecols)))
    labels = np.empty((0, 1))
    for equity in equities:
        data = pn.data.get(equity, startdate, enddate)
        print("{0} records retrieved for equity '{1}'".format(len(data.index), equity))
        # get labels as DataFrame
        eqlab = get_eqlabels(data, n_feat_sess, prediction_interval, labelcol, startdate, enddate)
        # create an empty ndarray with the correct number of rows and 0 columns
        eqfeatall = np.empty((data.shape[0] - n_feat_sess - prediction_interval + 1, 0))
        for featcol in featurecols:
            eqfeat = get_eqfeatures(data, n_feat_sess, prediction_interval, featcol, startdate, enddate)
            eqfeat = pn.data.normalize(eqfeat, method="mean")
            eqfeatall = np.append(eqfeatall, eqfeat.values, axis=1)
        features = np.append(features, eqfeatall, axis=0)
        labels = np.append(labels, eqlab.values, axis=0)
    features = pn.data.add_const(features)
    return features, labels

def save(fname, features, labels):
    # combine features and labels into a single ndarray
    data = np.empty((features.shape[0], features.shape[1] + 1))
    data[:, :1] = labels
    data[:, 1:] = features
    # save the result
    np.save(fname, data)

def load(fname):
    """
    Retrieve features and labels from csv file
    """
    #data = np.loadtxt(fname, delimiter=',', dtype='float64')
    data = np.load(fname)
    return data[:, 1:], data[:, :1]
