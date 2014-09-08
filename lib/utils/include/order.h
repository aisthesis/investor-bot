/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order.h
 *
 * class representing an order
 *
 * Author Marshall Farrier
 * Since 2014-08-27
 */

#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
public:
    // For naming convention cf.:
    // http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Enumerator_Names
    enum class Type { kBuy, kSell };
    enum class Mode { kLimit, kMarket, kStopLoss };
    
private:
    Type type_;
    Mode mode_;
    std::string ticker_;
    int shares_;
    double share_price_;

public:
    Order(const Type &, const Mode &, const std::string &, const int &, const double &);
    Order(const Order &);
    ~Order() {}

    Type type() const;
    Mode mode() const;
    std::string ticker() const;
    int shares() const;
    double share_price() const;

    bool fillable(const double &) const;
    bool fillable(const double &, const double &) const;

    bool operator==(const Order &) const;
    bool operator!=(const Order &) const;
};
#endif
