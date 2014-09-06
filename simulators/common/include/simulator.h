/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * simulator.h
 *
 * Simulator class
 *
 * Author Marshall Farrier
 * Since 2014-09-03
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "investor.h"
#include "globals.h"
#include "order_action.h"

class Simulator {
private:
    Investor *investor_;
    const std::vector<DailyOhlcs> ohlc_data_;
    const std::vector<DailyRecommendations> recommendations_;

    // populated on run:
    std::vector<OrderAction> actions_;
    std::string start_date_;
    double start_value_;
    std::string end_date_;
    double end_value_;
public:
    // both price data and recommendations must be sorted (earliest date first) for the simulator
    // to work properly
    Simulator(Investor &, const std::vector<DailyOhlcs> &, const std::vector<DailyRecommendations> &);
    ~Simulator() {}

    void run();
    std::vector<OrderAction> actions() const;
    double start_value() const;
    double end_value() const;
    std::string start_date() const;
    std::string end_date() const;
    virtual double commission() const;
private:
    void process_standing_orders(const std::string &date, const std::vector<Order> &orders, 
            const TickerOhlcMap &ohlc_map);
};
#endif
