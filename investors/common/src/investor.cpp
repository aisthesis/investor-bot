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
}

Investor::~Investor() {
    delete portfolio_;
}

Portfolio *Investor::portfolio() const {
    return portfolio_;
}
