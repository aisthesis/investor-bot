/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order.cpp
 *
 * class representing an order
 *
 * Author Marshall Farrier
 * Since 2014-08-27
 */

#include <string>
#include "order.h"

Order::Order(const Type &type, const Mode &mode, const std::string &ticker, 
    const int &shares, const double &share_price) {
    type_ = type;
    mode_ = mode;
    ticker_ = ticker;
    shares_ = shares;
    share_price_ = share_price;
}

Order::Type Order::type() const {
    return type_;
}

Order::Mode Order::mode() const {
    return mode_;
}

std::string Order::ticker() const {
    return ticker_;
}

int Order::shares() const {
    return shares_;
}

double Order::share_price() const {
    return share_price_;
}

bool Order::fillable(const double &mkt_price) const {
    if (mode_ == Mode::kMarket || share_price_ == mkt_price) return true;
    if (share_price_ < mkt_price) {
        if (type_ == Type::kSell && mode_ == Mode::kLimit) return true;
        if (type_ == Type::kBuy && mode_ == Mode::kStopLoss) return true;
        return false;
    }
    // reaching here means: mkt_price < share_price_
    if (type_ == Type::kBuy && mode_ == Mode::kLimit) return true;
    if (type_ == Type::kSell && mode_ == Mode::kStopLoss) return true;
    return false;
}
