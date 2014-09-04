/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * ohlc.h
 *
 * Simple struct for storing ohlc data
 *
 * Author Marshall Farrier
 * Since 2014-09-03
 */

#ifndef OHLC_H
#define OHLC_H

struct Ohlc {
    double open;
    double high;
    double low;
    double close;
};
#endif
