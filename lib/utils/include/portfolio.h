/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * portfolio.h
 *
 * class representing a stock portfolio, including cash
 *
 * Author Marshall Farrier
 * Since 2014-08-25
 */

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <unordered_map>

#include "ohlc.h"

class Portfolio {
private:
    double cash_;
    std::unordered_map<std::string, int> *stocks_;
public:
    Portfolio();
    Portfolio(const double &);
    ~Portfolio();

    double cash() const;
    void deposit(const double &);
    // no built-in check for negative result
    void withdraw(const double &);
    // always succeeds but can be on margin
    void buy(const std::string &equity, const int &shares, const double &cost);
    // always succeeds, but possibly on margin 
    void sell(const std::string &equity, const int &shares, const double &value);
    int shares(const std::string &) const;
    int n_long_pos() const;
    int n_short_pos() const;
    // get portfolio value given share prices of stocks owned
    double value(const std::unordered_map<std::string, double> &price_table) const;
    double value(const std::unordered_map<std::string, Ohlc> &price_table) const;
    // iterator through stocks
    std::unordered_map<std::string, int>::iterator begin() const;
    std::unordered_map<std::string, int>::iterator end() const;
private:
    void add_shares(const std::string &equity, const int &shares);
};
#endif
