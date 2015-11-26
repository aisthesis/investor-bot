"""
Visualize equity data

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

import matplotlib
import matplotlib.pyplot as plt

import constants

def prices(vdat, forecast_interval, title='Prices'):
    if forecast_interval not in [2**i for i in 
            range(constants.PRED_RANGE_BEGIN, constants.PRED_RANGE_END)]:
        raise ValueError('unknown forecast interval')
    int_label = str(forecast_interval)
    columns = ['Price', 'Ave Price ' + int_label, 'Pred Price ' + int_label]
    plt.figure()
    vdat[columns[0]].plot(color='blue', legend=True)
    vdat[columns[1]].plot(color='grey', legend=True)
    vdat[columns[2]].plot(color='red', legend=True)
    plt.suptitle(title)
    plt.show()
    plt.close()

def growth(vdat, forecast_interval, title='Growth'):
    if forecast_interval not in [2**i for i in 
            range(constants.PRED_RANGE_BEGIN, constants.PRED_RANGE_END)]:
        raise ValueError('unknown forecast interval')
    plt.figure()
    plt.suptitle(title)
    plt.show()
    plt.close()

