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
 * Simply follows the recommendation.
 * Note that available cash is not checked in placing a buy order.
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <string>
#include <unordered_map>
#include <vector>

#include "investor01.h"
#include "portfolio.h"
#include "order.h"
#include "investor_constants.h"

std::vector<Order> Investor01::order(const std::string &ticker, const double &strength,
        const std::unordered_map<std::string, double> &price_table) const {
    std::vector<Order> orders;
    // sell recommendation
    if (strength < investor::kSellHoldThreshold) {
        // we are long the given stock
        if (this->portfolio()->shares(ticker) > 0) {
            orders.push_back(Order(Order::Type::kSell, Order::Mode::kLimit, ticker,
                    this->portfolio()->shares(ticker), price_table.at(ticker)));
        }
        // no shares owned
        return orders;
    }
    // hold recommendation: do nothing
    if (strength < investor::kHoldBuyThreshold) {
        return orders;
    }
    // buy recommendation
    // no shares owned: buy them (otherwise do nothing)
    if (this->portfolio()->shares(ticker) <= 0) {
        orders.push_back(Order(Order::Type::kBuy, Order::Mode::kLimit, ticker,
                shares_to_buy(ticker, price_table) - this->portfolio()->shares(ticker), 
                price_table.at(ticker)));
    }
    return orders;
}

int Investor01::shares_to_buy(const std::string &ticker, 
        const std::unordered_map<std::string, double> &price_table) const {
    double to_invest = this->portfolio()->value(price_table) / this->n_watched();
    return static_cast<int>(to_invest / price_table.at(ticker));
}
