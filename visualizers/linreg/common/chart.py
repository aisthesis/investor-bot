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
    distlab = _distance_label(forecast_interval)
    columns = ['Price', 'Ave Price ' + distlab, 'Pred Price ' + distlab]
    plt.figure()
    vdat[columns[0]].plot(color='blue', legend=True)
    vdat[columns[1]].plot(color='grey', legend=True)
    vdat[columns[2]].plot(color='red', legend=True)
    plt.suptitle(title)
    plt.show()
    plt.close()

def growth(vdat, forecast_interval, title='Growth'):
    distlab = _distance_label(forecast_interval)
    pricecol = 'Price'
    avegrowthcol = 'Ave Growth ' + distlab
    predgrowthcol = 'Pred Growth ' + distlab
    #matplotlib.style.use('ggplot')
    plt.figure()
    ax1 = plt.subplot2grid((3, 6), (0, 0), rowspan=2, colspan=6)
    ax1.grid(True)
    plt.ylabel(pricecol)
    plt.setp(plt.gca().get_xticklabels(), visible=False)
    ax1.plot(vdat.index, vdat.loc[:, pricecol], color='blue')
    ax2 = plt.subplot2grid((3, 6), (2, 0), sharex=ax1, rowspan=1, colspan=6)
    ax2.grid(True)
    plt.ylabel('Predicted Growth')
    ax2.plot(vdat.index, vdat.loc[:, avegrowthcol], color='grey')
    ax2.plot(vdat.index, vdat.loc[:, predgrowthcol], color='red')
    plt.suptitle(title)
    plt.show()
    plt.close()

def _distance_label(forecast_interval):
    if forecast_interval not in [2**i for i in 
            range(constants.PRED_RANGE_BEGIN, constants.PRED_RANGE_END)]:
        raise ValueError('unknown forecast interval')
    return str(forecast_interval)

