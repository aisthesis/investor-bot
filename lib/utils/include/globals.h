/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * globals.h
 *
 * global constants and definitions
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <unordered_map>
#include <string>

#include "ohlc.h"

// key is ticker
typedef std::unordered_map<std::string, Ohlc> TickerOhlcMap;
// key is a date string
typedef std::unordered_map<std::string, TickerOhlcMap> DailyOhlcs;
// key is a ticker
typedef std::unordered_map<std::string, double> DailyRecommendations;

namespace investor {
    constexpr double kSellHoldThreshold = 1.0 / 3.0;
    constexpr double kHoldBuyThreshold = 2.0 / 3.0;
}
#endif
