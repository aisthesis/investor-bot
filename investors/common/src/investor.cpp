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

double Investor::cash() const {
    return portfolio_->cash();
}

void Investor::deposit(const double &amt) {
    portfolio_->deposit(amt);
}

void Investor::withdraw(const double &amt) {
    portfolio_->withdraw(amt);
}

void Investor::buy(const std::string &equity, const int &shares, const double &cost) {
    portfolio_->buy(equity, shares, cost);
}

void Investor::sell(const std::string &equity, const int &shares, const double &value) {
    portfolio_->sell(equity, shares, value);
}

int Investor::shares(const std::string &ticker) const {
    return portfolio_->shares(ticker);
}

int Investor::n_long_pos() const {
    return portfolio_->n_long_pos();
}

int Investor::n_short_pos() const {
    return portfolio_->n_short_pos();
}

double Investor::value(const std::unordered_map<std::string, double> &price_table) const {
    return portfolio_->value(price_table);
}

// iterator through stocks in portfolio
std::unordered_map<std::string, int>::iterator Investor::pfbegin() const {
    return portfolio_->begin();
}

std::unordered_map<std::string, int>::iterator Investor::pfend() const {
    return portfolio_->end();
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
