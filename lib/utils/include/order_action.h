/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order_action.h
 *
 * class representing any action that can be taken on an order.
 * Like Order objects, OrderAction objects are immutable.
 * A total is included to allow for commission or other possible
 * discrepancies between shares * share_price and actual total.
 *
 * Author Marshall Farrier
 * Since 2014-09-04
 */

#ifndef ORDER_ACTION_H
#define ORDER_ACTION_H

#include <string>

#include "order.h"
#include "order_action.h"

class OrderAction {
public:
    // For naming convention cf.:
    // http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Enumerator_Names
    enum class Act { kPlace, kFill, kCancel };
    
private:
    std::string date_;
    Act act_;
    Order order_;
    double total_;

public:
    // Note that total should be negative for buy orders (amount will be SUBTRACTED from available cash)
    // and positive for sell orders (amount will be ADDED to available cash)
    OrderAction(const std::string &date, const Act &act, const Order &order, const double &total = 0.0); 
    ~OrderAction() {}

    std::string date() const;
    Act act() const;
    Order order() const;
    double total() const;

    bool operator==(const OrderAction &) const;
    bool operator!=(const OrderAction &) const;
};
#endif
