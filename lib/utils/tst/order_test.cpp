/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order_test.cpp
 *
 * tests for Order struct
 *
 * Author Marshall Farrier
 * Since 2014-08-27
 */

#include <iostream>
#include <string>

#include "globals.h"
#include "order.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

bool approx(const double &, const double &);
// return false if a test has failed
bool show_msg(const char *, const bool &, int &, int &);

int main() {
    int passed = 0,
        failed = 0;
    std::string ticker = "blah";
    int shares = 5;
    double share_price = 3.14159;
    double low_mkt_price = 3.0;
    double lower_mkt_price = 2.9;
    double high_mkt_price = 3.15;
    double higher_mkt_price = 3.2;

    std::cout << "Testing order type BUY:" << std::endl;
    // Mode kLimit
    Order *order = new Order(Order::Type::kBuy, Order::Mode::kLimit, ticker, shares, share_price);  
    // Properly constructed (getters)
    show_msg("correct type", order->type() == Order::Type::kBuy, passed, failed);
    show_msg("correct mode", order->mode() == Order::Mode::kLimit, passed, failed);
    show_msg("correct ticker", order->ticker() == ticker, passed, failed);
    show_msg("correct shares", order->shares() == shares, passed, failed);
    show_msg("correct share_price", approx(order->share_price(), share_price), passed, failed);
    show_msg("limit buy order: equality", 
            *order == Order(Order::Type::kBuy, Order::Mode::kLimit, ticker, shares, share_price),
            passed, failed);
    show_msg("limit buy order: inequality", 
            *order != Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price),
            passed, failed);

    // fillable()
    show_msg("limit buy order: mkt below limit", order->fillable(low_mkt_price), passed, failed);
    show_msg("limit buy order: mkt above limit", !order->fillable(high_mkt_price), passed, failed);
    show_msg("limit buy order: range below limit", order->fillable(low_mkt_price, lower_mkt_price), passed, failed);
    show_msg("limit buy order: range above limit", !order->fillable(high_mkt_price, higher_mkt_price), passed, failed);
    show_msg("limit buy order: range includes limit", order->fillable(high_mkt_price, low_mkt_price), passed, failed);
    delete order;

    // Mode kStopLoss
    order = new Order(Order::Type::kBuy, Order::Mode::kStopLoss, ticker, shares, share_price);
    show_msg("stop-loss buy order: mkt below limit", !order->fillable(low_mkt_price), passed, failed);
    show_msg("stop-loss buy order: mkt above limit", order->fillable(high_mkt_price), passed, failed);
    show_msg("stop-loss buy order: range below limit", !order->fillable(low_mkt_price, lower_mkt_price), passed, failed);
    show_msg("stop-loss buy order: range above limit", order->fillable(high_mkt_price, higher_mkt_price), passed, failed);
    show_msg("stop-loss buy order: range includes limit", order->fillable(high_mkt_price, low_mkt_price), passed, failed);
    show_msg("stop-loss buy order: equality", 
            *order == Order(Order::Type::kBuy, Order::Mode::kStopLoss, ticker, shares, share_price),
            passed, failed);
    show_msg("stop-loss buy order: inequality", 
            *order != Order(Order::Type::kBuy, Order::Mode::kLimit, ticker, shares, share_price),
            passed, failed);
    delete order;

    // Mode Market
    order = new Order(Order::Type::kBuy, Order::Mode::kMarket, ticker, shares, share_price);
    show_msg("market buy order: mkt below limit", order->fillable(low_mkt_price), passed, failed);
    show_msg("market buy order: mkt above limit", order->fillable(high_mkt_price), passed, failed);
    show_msg("market buy order: range below limit", order->fillable(low_mkt_price, lower_mkt_price), passed, failed);
    show_msg("market buy order: range above limit", order->fillable(high_mkt_price, higher_mkt_price), passed, failed);
    show_msg("market buy order: range includes limit", order->fillable(high_mkt_price, low_mkt_price), passed, failed);
    show_msg("market buy order: equality", 
            *order == Order(Order::Type::kBuy, Order::Mode::kMarket, ticker, shares, share_price),
            passed, failed);
    show_msg("market buy order: inequality", 
            *order != Order(Order::Type::kBuy, Order::Mode::kMarket, "notblah", shares, share_price),
            passed, failed);
    delete order;

    std::cout << "Testing order type SELL:" << std::endl;
    // Mode kLimit
    order = new Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price);  
    show_msg("limit sell order: mkt below limit", !order->fillable(low_mkt_price), passed, failed);
    show_msg("limit sell order: mkt above limit", order->fillable(high_mkt_price), passed, failed);
    show_msg("limit sell order: range below limit", !order->fillable(low_mkt_price, lower_mkt_price), passed, failed);
    show_msg("limit sell order: range above limit", order->fillable(high_mkt_price, higher_mkt_price), passed, failed);
    show_msg("limit sell order: range includes limit", order->fillable(high_mkt_price, low_mkt_price), passed, failed);
    show_msg("limit buy order: equality", 
            *order == Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price),
            passed, failed);
    show_msg("limit buy order: inequality", 
            *order != Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares + 1, share_price),
            passed, failed);
    delete order;

    // Mode kStopLoss
    order = new Order(Order::Type::kSell, Order::Mode::kStopLoss, ticker, shares, share_price);
    show_msg("stop-loss sell order: mkt below limit", order->fillable(low_mkt_price), passed, failed);
    show_msg("stop-loss sell order: mkt above limit", !order->fillable(high_mkt_price), passed, failed);
    show_msg("stop-loss sell order: range below limit", order->fillable(low_mkt_price, lower_mkt_price), passed, failed);
    show_msg("stop-loss sell order: range above limit", !order->fillable(high_mkt_price, higher_mkt_price), passed, failed);
    show_msg("stop-loss sell order: range includes limit", order->fillable(high_mkt_price, low_mkt_price), passed, failed);
    show_msg("stop-loss buy order: equality", 
            *order == Order(Order::Type::kSell, Order::Mode::kStopLoss, ticker, shares, share_price),
            passed, failed);
    show_msg("stop-loss buy order: inequality", 
            *order != Order(Order::Type::kSell, Order::Mode::kStopLoss, ticker, shares, share_price + 1.0),
            passed, failed);
    delete order;

    // Mode Market
    order = new Order(Order::Type::kSell, Order::Mode::kMarket, ticker, shares, share_price);
    show_msg("market sell order: mkt below limit", order->fillable(low_mkt_price), passed, failed);
    show_msg("market sell order: mkt above limit", order->fillable(high_mkt_price), passed, failed);
    show_msg("market sell order: range below limit", order->fillable(low_mkt_price, lower_mkt_price), passed, failed);
    show_msg("market sell order: range above limit", order->fillable(high_mkt_price, higher_mkt_price), passed, failed);
    show_msg("market sell order: range includes limit", order->fillable(high_mkt_price, low_mkt_price), passed, failed);
    show_msg("limit buy order: equality", 
            *order == Order(Order::Type::kSell, Order::Mode::kMarket, ticker, shares, share_price),
            passed, failed);
    show_msg("limit buy order: inequality", 
            *order != Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price),
            passed, failed);
    delete order;

    std::cout << passed << " tests passed." << std::endl
        << (failed > 0 ? BOLDRED : RESET) << failed << " tests failed." << RESET << std::endl << std::endl;
    
    return 0;
}

bool approx(const double &x1, const double &x2) {
    if (x1 >= x2) return x1 - x2 < kEpsilon;
    return x2 - x1 < kEpsilon;
}

bool show_msg(const char *tst_desc, const bool &passing_condition, int &passed, int &failed) {
    if (passing_condition) {
        ++passed;
        return true;
    }
    ++failed;
    std::cout << BOLDRED << "test failed: " << tst_desc << RESET << std::endl << std::endl;
    return false;
}
