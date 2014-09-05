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

#include "order.h"
#include "order_action.h"

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
