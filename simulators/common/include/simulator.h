/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * simulator.h
 *
 * Simulator class
 *
 * Author Marshall Farrier
 * Since 2014-09-03
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "investor.h"
#include "ohlc.h"

// key is ticker
typedef std::unordered_map<std::string, Ohlc> TickerPriceRangeMap;
// key is a date string
typedef std::unordered_map<std::string, TickerPriceRangeMap> DailyPriceRanges;
// key is a ticker
typedef std::unordered_map<std::string, double> DailyRecommendations;

class Simulator {
private:
    Investor *investor_;
    std::vector<DailyPriceRanges> price_data_;
    std::vector<DailyRecommendations> recommendations_;
public:
    Simulator() {}
    ~Simulator() {}
};
#endif
