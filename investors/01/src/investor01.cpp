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
 * Unless the simulator contains logic to prevent it, 
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <string>
#include <unordered_map>

#include "investor01.h"
#include "portfolio.h"
#include "investor_constants.h"

Order Investor01::order(const std::string &ticker, const double &strength,
        const std::unordered_map<std::string, double> &price_table) const {
    Order do_nothing(Order::Type::kSell, Order::Mode::kLimit, ticker, 0, 0.0);
    // sell recommendation
    if (strength < investor::kSellHoldThreshold) {
        // we are long the given stock
        if (this->portfolio()->shares(ticker) > 0) {
            return Order(Order::Type::kSell, Order::Mode::kLimit, ticker,
                    this->portfolio()->shares(ticker), price_table.at(ticker));
        }
        // no shares owned
        return do_nothing;
    }
    // hold recommendation: do nothing
    if (strength < investor::kHoldBuyThreshold) {
        return do_nothing;
    }
    // buy recommendation
    // stock already owned: do nothing
    if (this->portfolio()->shares(ticker) > 0) return do_nothing;
    // no shares owned: buy
    return Order(Order::Type::kBuy, Order::Mode::kLimit, ticker, 
            shares_to_buy(ticker, price_table), price_table.at(ticker));
}

int Investor01::shares_to_buy(const std::string &ticker, 
        const std::unordered_map<std::string, double> &price_table) const {
    double to_invest = this->portfolio()->value(price_table) / this->n_watched();
    return static_cast<int>(to_invest / price_table.at(ticker));
}
