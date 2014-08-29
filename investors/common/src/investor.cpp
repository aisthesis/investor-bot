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

bool Investor::watches(const std::string &ticker) const {
    return watch_list_.count(ticker) > 0;
}

Investor &Investor::watch(const std::string &ticker) {
    watch_list_.insert(ticker);
    return *this;
}

void Investor::unwatch(const std::string &ticker) {
    watch_list_.erase(ticker);
}

int Investor::n_watched() const {
    return watch_list_.size();
}

Portfolio *Investor::portfolio() const {
    return portfolio_;
}
