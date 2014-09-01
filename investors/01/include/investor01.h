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

class Investor01 : public Investor {
private:
    // reserved for pending buy orders
    double pending_purchases_;
public:
    Investor01(); 
    ~Investor01() {}

    // order for 0 shares if no action
    // this is where all of the investor logic goes:
    std::vector<Order> order(const std::unordered_map<std::string, double> &strengths,
            const std::unordered_map<std::string, double> &price_table);
    double pending() const;
    void clear_pending();
    // return total after adding given amount
    double add_to_pending(const double &);

private:
    int shares_to_buy(const std::string &ticker, 
            const std::unordered_map<std::string, double> &price_table) const;
    void process_recommendation(std::vector<Order> &orders, const std::string &ticker,
            const double &strength, const std::unordered_map<std::string, double> &price_table);
};
#endif
