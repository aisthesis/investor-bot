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
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <string>
#include "investor01.h"
#include "portfolio.h"

Order Investor01::order(const std::string &ticker, const double &strength) const {
    Order order(Order::Type::kBuy, Order::Mode::kLimit, ticker, 0, 0.0);
    return order;
}
