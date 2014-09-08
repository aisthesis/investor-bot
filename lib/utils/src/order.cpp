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

#include "globals.h"
#include "order.h"

Order::Order(const Type &type, const Mode &mode, const std::string &ticker, 
    const int &shares, const double &share_price) {
    type_ = type;
    mode_ = mode;
    ticker_ = ticker;
    shares_ = shares;
    share_price_ = share_price;
}

Order::Order(const Order &order) 
        : Order(order.type_, order.mode_, order.ticker_, order.shares_, order.share_price_) {}

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
    return fillable(mkt_price, mkt_price);
}

bool Order::fillable(const double &range_begin, const double &range_end) const {
    if (mode_ == Mode::kMarket) return true;
    double lower_bound = range_begin,
        upper_bound = range_end;

    if (lower_bound > upper_bound) {
        lower_bound = range_end;
        upper_bound = range_begin;
    }

    if (lower_bound <= share_price_ && share_price_ <= upper_bound) return true;
    if (share_price_ < lower_bound) {
        if (type_ == Type::kSell && mode_ == Mode::kLimit) return true;
        if (type_ == Type::kBuy && mode_ == Mode::kStopLoss) return true;
        return false;
    }
    // reaching here means upper_bound < share_price_
    if (type_ == Type::kBuy && mode_ == Mode::kLimit) return true;
    if (type_ == Type::kSell && mode_ == Mode::kStopLoss) return true;
    return false;
}

bool Order::operator==(const Order &other) const {
    return this->type_ == other.type_ && this->mode_ == other.mode_ && this->ticker_ == other.ticker_
            && this->shares_ == other.shares_ && -kEpsilon < (this->share_price_ - other.share_price_)
            && (this->share_price_ - other.share_price_) < kEpsilon;
}

bool Order::operator!=(const Order &other) const {
    return !(*this == other);
}
