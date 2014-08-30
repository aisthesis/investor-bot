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
#include "portfolio.h"
#include "order.h"
#include "investor.h"

class Investor01 : public Investor {
public:
    Investor01() {} 
    ~Investor01() {}

    // order for 0 shares if no action
    // this is where all of the investor logic goes:
    Order order(const std::string &ticker, const double &strength) const;
};
#endif
