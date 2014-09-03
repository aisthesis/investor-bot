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

#include "investor01.h"
#include "portfolio.h"
#include "order.h"
#include "investor_constants.h"

// public
Investor01::Investor01() {
    pending_purchases_ = 0.0;
}

std::vector<Order> Investor01::order(const std::unordered_map<std::string, double> &strengths,
        const std::unordered_map<std::string, double> &price_table) {
    std::vector<Order> orders;
    // sort recommendations to buy strongest stocks first
    std::vector<std::pair<std::string, double> > strengths_desc(strengths.begin(), strengths.end());
    std::sort(strengths_desc.begin(), strengths_desc.end(), [](std::pair<std::string, double> x1,
            std::pair<std::string, double> x2) { return x1.second >= x2.second; });
    for (const auto &strength : strengths_desc) {
        process_recommendation(orders, strength.first, strength.second, price_table);
    }
    return orders;
}

// private
int Investor01::shares_to_buy(const std::string &ticker, 
        const std::unordered_map<std::string, double> &price_table) const {
    int shares = 0;
    double to_invest = this->portfolio()->value(price_table) / price_table.size(),
        available = this->portfolio()->cash() - pending_purchases_;
    // if enough cash present, just buy
    if (to_invest <= available) { 
        shares = static_cast<int>(to_invest / price_table.at(ticker));
    }
    else if (0.5 * to_invest <= available) {
        // at least half of desired investment is available in cash
        shares = static_cast<int>(available / price_table.at(ticker));
    }
    // if we don't even have half of desired investment, return 0
    return shares;
}

void Investor01::process_recommendation(std::vector<Order> &orders, const std::string &ticker,
        const double &strength, const std::unordered_map<std::string, double> &price_table) {
    // sell recommendation
    if (strength < investor::kSellHoldThreshold) {
        // we are long the given stock
        if (this->portfolio()->shares(ticker) > 0) {
            // if a sell order exists (e.g., to raise funds for a buy), delete it
            // because we're selling the whole position
            std::vector<Order>::iterator it = find_if(orders.begin(), orders.end(), 
                    [&](Order order) { return order.ticker() == ticker; });
            if (it != orders.end()) {
                orders.erase(it);
            }
            orders.push_back(Order(Order::Type::kSell, Order::Mode::kLimit, ticker,
                    this->portfolio()->shares(ticker), price_table.at(ticker)));
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
    if (this->portfolio()->shares(ticker) <= 0) {
        int shares = shares_to_buy(ticker, price_table);
        if (shares > 0) {
            orders.push_back(Order(Order::Type::kBuy, Order::Mode::kLimit, ticker,
                    shares, price_table.at(ticker)));
        }
        else {
            // sell enough for a future buy
            sell_part_of_each(orders, price_table, 1.0 / (this->portfolio()->n_long_pos() + 1));
        }
    }
}

void Investor01::sell_part_of_each(std::vector<Order> &orders, 
        const std::unordered_map<std::string, double> &price_table, const double &portion) const {
    int shares = 0;

    for (auto it = this->portfolio()->begin(); it != this->portfolio()->end(); it++) {
        shares = static_cast<int>(portion * it->second);    
        if (shares > 0) {
            orders.push_back(Order(Order::Type::kSell, Order::Mode::kLimit, it->first,
                shares, price_table.at(it->first)));
        }
    }
}
