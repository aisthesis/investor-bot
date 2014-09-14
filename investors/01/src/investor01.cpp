/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor01.cpp
 *
 * investor implementation 01
 * Implements a vector of recommendations.
 * Sale recommendations: sell entire position
 * Hold recommendations: do nothing
 * Buy recommendations: 
 * - stock already owned: do nothing
 * - not already owned: buy if possible without margining account.
 *   shares to buy: 
 *   1) Get net worth from portfolio. 
 *   2) Subtract amounts already reserved for pending purchases.
 *   3) Divide this amount by the number of items in the price table.
 *      So, if the price table includes 7 stocks, 1 / 7 of portfolio
 *      value will be allocated to the current buy order, unless that
 *      amount exceeds available cash.
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
// TODO remove
#include <iostream>

#include "investor01.h"
#include "portfolio.h"
#include "order.h"
#include "globals.h"

// public
std::vector<Order> Investor01::order(const std::unordered_map<std::string, double> &strengths,
        const TickerOhlcMap &ohlc_map) {
    std::vector<Order> orders;
    if (strengths.size() > 6) {
        std::cout << "converting strength map to vector" << std::endl;
    }
    // sort recommendations to buy strongest stocks first
    std::vector<std::pair<std::string, double> > strengths_desc;
    if (strengths.size() > 6) {
        std::cout << "populating vector" << std::endl;
    }
    for (auto it = strengths.begin(); it != strengths.end(); ++it) {
        strengths_desc.push_back({it->first, it->second});
    }
    std::sort(strengths_desc.begin(), strengths_desc.end(), [](std::pair<std::string, double> x1,
            std::pair<std::string, double> x2) { return x1.second >= x2.second; });
    for (const auto &strength : strengths_desc) {
        process_recommendation(orders, strength.first, strength.second, ohlc_map);
    }
    return orders;
}

// private
int Investor01::shares_to_buy(const std::string &ticker, 
        const TickerOhlcMap &ohlc_map) const {
    int shares = 0;
    double to_invest = this->value(ohlc_map) / ohlc_map.size(),
        available = this->cash() - this->pending();
    // if enough cash present, just buy
    if (to_invest <= available) { 
        shares = static_cast<int>(to_invest / ohlc_map.at(ticker).close);
    }
    else if (0.5 * to_invest <= available) {
        // at least half of desired investment is available in cash
        shares = static_cast<int>(available / ohlc_map.at(ticker).close);
    }
    // if we don't even have half of desired investment, return 0
    return shares;
}

void Investor01::process_recommendation(std::vector<Order> &orders, const std::string &ticker,
        const double &strength, const TickerOhlcMap &ohlc_map) {
    if (ticker == "f") {
        std::cout << "processing 'f' recommendation" << std::endl;
    }
    // sell recommendation
    if (strength < investor::kSellHoldThreshold) {
        // we are long the given stock
        if (this->shares(ticker) > 0) {
            // if a sell order exists (e.g., to raise funds for a buy), delete it
            // because we're selling the whole position
            std::vector<Order>::iterator it = find_if(orders.begin(), orders.end(), 
                    [&](Order order) { return order.ticker() == ticker; });
            if (it != orders.end()) {
                orders.erase(it);
            }
            orders.push_back(Order(Order::Type::kSell, Order::Mode::kLimit, ticker,
                    this->shares(ticker), ohlc_map.at(ticker).close));
        }
        // no shares owned: do nothing
        return;
    }
    // hold recommendation: do nothing
    if (strength < investor::kHoldBuyThreshold) {
        return;
    }
    // buy recommendation
    // no shares owned: buy them (otherwise do nothing)
    if (this->shares(ticker) <= 0) {
        std::cout << "trying to buy '" << ticker << "'" << std::endl;
        int shares = shares_to_buy(ticker, ohlc_map);
        
        if (shares > 0) {
            orders.push_back(Order(Order::Type::kBuy, Order::Mode::kLimit, ticker,
                    shares, ohlc_map.at(ticker).close));
            this->add_to_pending(ohlc_map.at(ticker).close * shares);
        }
        else {
            // sell enough for a future buy
            sell_part_of_each(orders, ohlc_map, 1.0 / (this->n_long_pos() + 1));
        }
    }
}

void Investor01::sell_part_of_each(std::vector<Order> &orders, 
        const TickerOhlcMap &ohlc_map, const double &portion) const {
    int shares = 0;

    for (auto it = this->pfbegin(); it != this->pfend(); it++) {
        shares = static_cast<int>(portion * it->second);    
        if (shares > 0) {
            orders.push_back(Order(Order::Type::kSell, Order::Mode::kLimit, it->first,
                shares, ohlc_map.at(it->first).close));
        }
    }
}
