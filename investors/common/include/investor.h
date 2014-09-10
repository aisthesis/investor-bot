/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor.h
 *
 * abstract base Investor class
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#ifndef INVESTOR_H
#define INVESTOR_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "portfolio.h"
#include "order.h"
#include "globals.h"

class Investor {
private:
    Portfolio *portfolio_;
    double pending_purchases_;

public:
    Investor(); 
    ~Investor();

    // functions providing access to portfolio
    double cash() const;
    void deposit(const double &);
    void withdraw(const double &);
    void buy(const std::string &equity, const int &shares, const double &cost);
    void sell(const std::string &equity, const int &shares, const double &value);
    int shares(const std::string &) const;
    int n_long_pos() const;
    int n_short_pos() const;
    double value(const std::unordered_map<std::string, double> &price_table) const;
    double value(const std::unordered_map<std::string, Ohlc> &ohlc_table) const;
    // iterator through stocks in portfolio
    std::unordered_map<std::string, int>::iterator pfbegin() const;
    std::unordered_map<std::string, int>::iterator pfend() const;

    // functions related to pending purchases
    double pending() const;
    void clear_pending();
    // return total after adding given amount
    double add_to_pending(const double &);

    // this is where all of the investor logic goes:
    /**
     * Note that if an investor places market orders, it should still use a realistic
     * amount (such as closing price): While the amount is irrelevant in determining
     * whether or not a market order will be filled, it is the amount to be used
     * as an estimate for pending purchases
     */
    virtual std::vector<Order> order(const std::unordered_map<std::string, double> &strengths, 
            const TickerOhlcMap &ohlc_map) = 0;
};
#endif
