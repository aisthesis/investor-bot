/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * simulator.cpp
 *
 * Simulator class implementation
 *
 * Author Marshall Farrier
 * Since 2014-09-04
 */

#include "simulator.h"

Simulator::Simulator(Investor &investor, const std::vector<DailyOhlcs> &price_data, 
        const std::vector<DailyRecommendations> &recommendations) 
        : price_data_(price_data), recommendations_(recommendations) {
    investor_ = &investor;

    start_value_ = 0.0;
    end_value_ = 0.0;
}

void Simulator::run() {
    // TODO
}

std::vector<OrderAction> Simulator::actions() const {
    return actions_;
}

double Simulator::start_value() const {
    return start_value_;
}

double Simulator::end_value() const {
    return end_value_;
}

std::string Simulator::start_date() const {
    return start_date_;
}

std::string Simulator::end_date() const {
    return end_date_;
}
