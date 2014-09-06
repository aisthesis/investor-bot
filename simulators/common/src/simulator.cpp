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

#include <stdexcept>

#include "simulator.h"
#include "order.h"
#include "order_action.h"

Simulator::Simulator(Investor &investor, const std::vector<DailyOhlcs> &ohlc_data, 
        const std::vector<DailyRecommendations> &recommendations) 
        : ohlc_data_(ohlc_data), recommendations_(recommendations) {
    investor_ = &investor;

    start_value_ = 0.0;
    end_value_ = 0.0;
}

void Simulator::run() {
    std::vector<DailyRecommendations>::const_iterator rec_iter = recommendations_.cbegin();
    std::vector<DailyOhlcs>::const_iterator ohlc_iter = ohlc_data_.cbegin();
    std::vector<Order> standing_orders;

    // move ohlc_iter forward until dates match
    while (ohlc_iter->date != rec_iter->date && ohlc_iter != ohlc_data_.cend()) ++ohlc_iter;
    // throw exception if date ranges don't match
    if (ohlc_iter == ohlc_data_.cend()) {
        throw std::logic_error("no ohlc data to act on recommendations");
    }
    // set initial portfolio value using ohlc data from start date
    start_value_ = investor_->value(ohlc_iter->ohlc_values);
    while (ohlc_iter != ohlc_data_.cend() && rec_iter != recommendations_.cend()) {
        if (ohlc_iter->date != rec_iter->date) {
            throw std::logic_error("mismatched dates for recommendations and ohlc data");
        }
        // process standing_orders based on today's prices
        process_standing_orders(ohlc_iter->date, standing_orders, ohlc_iter->ohlc_values);

        // TODO
        ++ohlc_iter;
        ++rec_iter;
    }
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

double Simulator::commission() const {
    return 0.0;
}

// private helper functions
void Simulator::process_standing_orders(const std::string &date, const std::vector<Order> &orders, 
        const TickerOhlcMap &ohlc_map) {
    double amount = 0.0;
    for (auto &order : orders) {
        if (order.fillable(ohlc_map.at(order.ticker()).low, ohlc_map.at(order.ticker()).high)) {
            amount = order.share_price() * order.shares();
            if (order.type() == Order::Type::kBuy) {
                amount = -amount;
                investor_->add_to_pending(amount);
                amount -= commission();
                investor_->buy(order.ticker(), order.shares(), -amount);
            }
            else {
                amount -= commission();
                investor_->sell(order.ticker(), order.shares(), amount);
            }
            actions_.push_back(OrderAction(date, OrderAction::Act::kFill, Order(order), amount));
        }
        else {
            actions_.push_back(OrderAction(date, OrderAction::Act::kCancel, Order(order), 0.0));
        }
    }
}
