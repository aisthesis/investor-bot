/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor01.h
 *
 * investor implementation 01
 *
 * Author Marshall Farrier
 * Since 2014-08-29
 */

#ifndef INVESTOR01_H
#define INVESTOR01_H

#include <string>
#include <vector>
#include "portfolio.h"
#include "order.h"
#include "investor.h"
#include "globals.h"

class Investor01 : public Investor {
public:
    Investor01() {}
    ~Investor01() {}

    // this is where all of the investor logic goes, populating orders vector
    void order(std::vector<Order> *orders, const std::unordered_map<std::string, 
            double> &strengths, const TickerOhlcMap &ohlc_map);            

private:
    int shares_to_buy(const std::string &ticker, const TickerOhlcMap &ohlc_map) const;
    void process_recommendation(std::vector<Order> *orders, const std::string &ticker,
            const double &strength, const TickerOhlcMap &ohlc_map);
    void sell_part_of_each(std::vector<Order> *orders, const TickerOhlcMap &ohlc_map, 
            const double &portion) const;
};
#endif
