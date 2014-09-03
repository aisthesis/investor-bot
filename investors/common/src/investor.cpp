/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor.cpp
 *
 * abstract base Investor class
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <string>
#include "investor.h"
#include "portfolio.h"

Investor::Investor() {
    portfolio_ = new Portfolio();
    pending_purchases_ = 0.0;
}

Investor::~Investor() {
    delete portfolio_;
}

Portfolio *Investor::portfolio() const {
    return portfolio_;
}

double Investor::pending() const {
    return pending_purchases_;
}

void Investor::clear_pending() {
    pending_purchases_ = 0.0;
}

double Investor::add_to_pending(const double &amount) {
    pending_purchases_ += amount;
    return pending_purchases_;
}
