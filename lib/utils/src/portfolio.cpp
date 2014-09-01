/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * portfolio.cpp
 *
 * class representing a stock portfolio, including cash
 *
 * Author Marshall Farrier
 * Since 2014-08-25
 */

#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include "portfolio.h"

Portfolio::Portfolio() : Portfolio(0.0) {}

Portfolio::Portfolio(const double &cash) {
    cash_ = cash;
    stocks_ = new std::unordered_map<std::string, int>;
}

Portfolio::~Portfolio() {
    delete stocks_;
}

double Portfolio::cash() const {
    return cash_;
}

void Portfolio::deposit(const double &amt) {
    cash_ += amt;
}

// no built-in check for negative result
void Portfolio::withdraw(const double &amt) {
    cash_ -= amt;
}

// always succeeds but can be on margin
void Portfolio::buy(const std::string &equity, const int &shares, const double &cost) {
    cash_ -= cost;
    add_shares(equity, shares);
}

// always succeeds, but possibly on margin 
void Portfolio::sell(const std::string &equity, const int &shares, const double &value) {
    cash_ += value;
    add_shares(equity, -shares);
}

int Portfolio::shares(const std::string &equity) const {
    if (stocks_->count(equity) > 0) return (*stocks_)[equity];
    return 0;
}

int Portfolio::n_long_pos() const {
    return std::count_if(stocks_->begin(), stocks_->end(), 
        [](std::pair<std::string, int> it){ return it.second > 0; });
}

int Portfolio::n_short_pos() const {
    return std::count_if(stocks_->begin(), stocks_->end(), 
        [](std::pair<std::string, int> it){ return it.second < 0; });
}

void Portfolio::add_shares(const std::string &equity, const int &shares) {
    if (stocks_->count(equity) > 0) {
        (*stocks_)[equity] += shares;
    }
    else {
        (*stocks_)[equity] = shares;
    }
}

double Portfolio::value(const std::unordered_map<std::string, double> &price_table) const {
    double value = cash_;
    for (const auto &stock : *stocks_) {
        if (stock.second != 0) {
            // raise exception if stock not found in table
            if (price_table.count(stock.first) == 0) {
                throw std::invalid_argument("stock not present in price table");
            }
            value += price_table.at(stock.first) * stock.second;
        }
    }
    return value;
}
