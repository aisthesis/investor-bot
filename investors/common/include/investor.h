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

class Investor {
private:
    Portfolio *portfolio_;

public:
    Investor(); 
    ~Investor();

    Portfolio *portfolio() const;
    // order for 0 shares if no action
    // this is where all of the investor logic goes:
    virtual std::vector<Order> order(const std::unordered_map<std::string, double> &strengths, 
            const std::unordered_map<std::string, double> &price_list) = 0;
};
#endif
