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
    return orders;
}

double Investor01::pending() const {
    return pending_purchases_;
}

void Investor01::clear_pending() {
    pending_purchases_ = 0.0;
}

double Investor01::add_to_pending(const double &amount) {
    pending_purchases_ += amount;
    return pending_purchases_;
}

// private
int Investor01::shares_to_buy(const std::string &ticker, 
        const std::unordered_map<std::string, double> &price_table) const {
    double to_invest = this->portfolio()->value(price_table) / price_table.size();
    return static_cast<int>(to_invest / price_table.at(ticker));
}

void Investor01::process_recommendation(std::vector<Order> &orders, const std::string &ticker,
        const double &strength, const std::unordered_map<std::string, double> &price_table) {
    // sell recommendation
    if (strength < investor::kSellHoldThreshold) {
        // we are long the given stock
        if (this->portfolio()->shares(ticker) > 0) {
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
        int shares = shares_to_buy(ticker, price_table) - this->portfolio()->shares(ticker);
        double cost = price_table.at(ticker) * shares;
        if (cost <= this->portfolio()->cash() - pending_purchases_) {
            orders.push_back(Order(Order::Type::kBuy, Order::Mode::kLimit, ticker,
                    shares, price_table.at(ticker)));
        }
        else {
            // TODO
        }
    }
}
