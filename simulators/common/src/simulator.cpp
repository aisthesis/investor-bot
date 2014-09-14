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

Simulator::Simulator(Investor &investor, std::vector<DailyOhlcs> &ohlc_data, 
        std::vector<DailyRecommendations> &recommendations) {
    investor_ = &investor;
    ohlc_data_ = &ohlc_data;
    recommendations_ = &recommendations;
    start_value_ = 0.0;
    end_value_ = 0.0;
}

void Simulator::run() {
    std::vector<DailyRecommendations>::iterator rec_iter = recommendations_->begin();
    std::vector<DailyOhlcs>::iterator ohlc_iter = ohlc_data_->begin();
    std::vector<Order> standing_orders;

    // no recommendations
    if (rec_iter == recommendations_->end()) {
        throw std::logic_error("no recommendations on which to act");
    }
    // move ohlc_iter forward until dates match
    while (ohlc_iter != ohlc_data_->end() && ohlc_iter->date != rec_iter->date) ++ohlc_iter;
    // throw exception if date ranges don't match
    if (ohlc_iter == ohlc_data_->end()) {
        throw std::logic_error("no ohlc data to act on recommendations");
    }
    // set initial portfolio value using ohlc data from start date
    start_value_ = investor_->value(ohlc_iter->ohlc_values);
    start_date_ = ohlc_iter->date;
    while (ohlc_iter != ohlc_data_->end()) {
        if (rec_iter != recommendations_->end() && ohlc_iter->date != rec_iter->date) {
            throw std::logic_error("mismatched dates for recommendations and ohlc data");
        }
        // process standing_orders based on today's prices (this can still be done
        // even if we have processed all recommendations)
        process_standing_orders(ohlc_iter->date, standing_orders, ohlc_iter->ohlc_values);
        if (rec_iter == recommendations_->end()) break;
        standing_orders.clear();
        // get new orders (requires new recommendations)
        investor_->order(&standing_orders, rec_iter->recommendations, ohlc_iter->ohlc_values);
        // place standing orders
        for (auto &order : standing_orders) {
            actions_.push_back(OrderAction(rec_iter->date, OrderAction::Act::kPlace, order, 0.0));
        }
        ++ohlc_iter;
        ++rec_iter;
    }
    if (ohlc_iter == ohlc_data_->end()) --ohlc_iter;
    end_value_ = investor_->value(ohlc_iter->ohlc_values);
    end_date_ = ohlc_iter->date;
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
            if (order.type() == Order::Type::kBuy) {
                amount = -order.share_price() * order.shares();
                investor_->add_to_pending(amount);
                if (order.mode() == Order::Mode::kMarket) {
                    amount = -ohlc_map.at(order.ticker()).open * order.shares();
                }
                amount -= commission();
                investor_->buy(order.ticker(), order.shares(), -amount);
            }
            else {
                if (order.mode() == Order::Mode::kMarket) {
                    amount = ohlc_map.at(order.ticker()).open * order.shares();
                }
                else {
                    amount = order.share_price() * order.shares();
                }
                amount -= commission();
                investor_->sell(order.ticker(), order.shares(), amount);
            }
            actions_.push_back(OrderAction(date, OrderAction::Act::kFill, Order(order), amount));
        }
        else {
            if (order.type() == Order::Type::kBuy) {
                investor_->add_to_pending(-order.share_price() * order.shares());
            }
            actions_.push_back(OrderAction(date, OrderAction::Act::kCancel, Order(order), 0.0));
        }
    }
}
