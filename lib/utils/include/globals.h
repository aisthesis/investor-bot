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

struct Ohlc {
    double open;
    double high;
    double low;
    double close;
};

// keys are tickers
typedef std::unordered_map<std::string, Ohlc> TickerOhlcMap;

struct DailyOhlcs {
    std::string date;
    TickerOhlcMap ohlc_values;
};

struct DailyRecommendations {
    std::string date;
    std::unordered_map<std::string, double> recommendations;
};

// for floating point equality
constexpr double kEpsilon = 0.000001;
inline bool approx(const double &a, const double &b) {
    if (a <= b) return b - a < kEpsilon;
    return a - b < kEpsilon;
}

namespace investor {
    constexpr double kSellHoldThreshold = 1.0 / 3.0;
    constexpr double kHoldBuyThreshold = 2.0 / 3.0;
}
#endif
