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
#include "portfolio.h"
#include "order.h"

class Investor {
private:
    std::unordered_set<std::string> watch_list_;
    Portfolio *portfolio_;

public:
    Investor(); 
    ~Investor();

    bool watches(const std::string &) const;
    Investor &watch(const std::string &);
    void unwatch(const std::string &);
    int n_watched() const;
    Portfolio *portfolio() const;
    // order for 0 shares if no action
    // this is where all of the investor logic goes:
    virtual Order order(const std::string &ticker, const double &strength) const = 0;
};
#endif
