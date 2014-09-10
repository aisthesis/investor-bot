/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order_action.cpp
 *
 * class representing any action that can be taken on an order.
 * Like Order objects, OrderAction objects are immutable.
 * A total is included to allow for commission or other possible
 * discrepancies between shares * share_price and actual total.
 *
 * Author Marshall Farrier
 * Since 2014-09-04
 */

#include <string>
#include <ostream>
#include <iomanip>

#include "order.h"
#include "order_action.h"
#include "globals.h"

OrderAction::OrderAction(const std::string &date, const Act &act, 
        const Order &order, const double &total) 
        : date_(date), order_(order) {
    act_ = act;
    total_ = total;
}

std::string OrderAction::date() const {
    return date_;
}

OrderAction::Act OrderAction::act() const {
    return act_;
}

Order OrderAction::order() const {
    return order_;
}

double OrderAction::total() const {
    return total_;
}

bool OrderAction::operator==(const OrderAction &action) const {
    return this->date_ == action.date_ && this->act_ == action.act_ && this->order_ == action.order_
            && approx(this->total_, action.total_);
}

bool OrderAction::operator!=(const OrderAction &action) const {
    return !(*this == action);
}

std::ostream &operator<<(std::ostream &strm, const OrderAction::Act &act) {
    if (act == OrderAction::Act::kPlace) {
        return strm << "place";
    }
    if (act == OrderAction::Act::kFill) {
        return strm << "fill";
    }
    return strm << "cancel";
}

std::ostream &operator<<(std::ostream &strm, const OrderAction &action) {
    std::ios_base::fmtflags old_flags = strm.flags();

    strm << action.date_ << " " << action.act_ << " for " << std::fixed << std::setprecision(2)
        << action.total_ << " {" << action.order_ << "}";
    strm.flags(old_flags);
    return strm;
}
