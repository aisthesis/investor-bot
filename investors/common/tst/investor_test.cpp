/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor_test.cpp
 *
 * tests for abstract Investor class
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"

#include "investor.h"
#include "globals.h"

// concrete subclass for testing
class MyInvestor : public Investor {
    void order(std::vector<Order> *orders, const std::unordered_map<std::string, double> &strengths,
            const TickerOhlcMap &ohlc_map) {}
};

TEST_CASE("investor tests", "[Investor]") {
    std::string ticker1 = "blah",
        ticker2 = "foo";
    double deposit_amt = 1000.0,
        expected_cash = 0.0;
    int shares_bought = 5,
        shares_sold = 3;
    double purchase_price = 100.0,
        sale_price = 200.0,
        add_to_pending = 3.14;

    MyInvestor investor;

    SECTION("initialization") {
        REQUIRE(investor.n_long_pos() == 0);
        REQUIRE(approx(investor.cash(), 0.0));
        REQUIRE(approx(investor.pending(), 0.0));
    }

    SECTION("pending purchases") {
        double pending = investor.add_to_pending(add_to_pending);
        REQUIRE(approx(investor.pending(), add_to_pending));
        REQUIRE(approx(pending, add_to_pending));
        investor.clear_pending();
        REQUIRE(approx(investor.pending(), 0.0));
    }

    SECTION("portfolio") {
        investor.deposit(deposit_amt);
        expected_cash += deposit_amt;
        REQUIRE(approx(investor.cash(), expected_cash));
        investor.buy(ticker1, shares_bought, purchase_price);
        expected_cash -= purchase_price;
        REQUIRE(approx(investor.cash(), expected_cash));
        REQUIRE(investor.n_long_pos() == 1);
        REQUIRE(investor.shares(ticker1) == shares_bought);
        investor.sell(ticker1, shares_sold, sale_price);
        expected_cash += sale_price;
        REQUIRE(approx(investor.cash(), expected_cash));
        REQUIRE(investor.n_long_pos() == 1);

        SECTION("iterator") {
            int counter = 0,
                tmp_shares = 0;
            std::string tmp_ticker = "";
            for (auto it = investor.pfbegin(); it != investor.pfend(); ++it) {
                ++counter;
                tmp_ticker = it->first;
                tmp_shares = it->second;
            }
            REQUIRE(counter == 1);
            REQUIRE(tmp_ticker == ticker1);
            REQUIRE(tmp_shares == shares_bought - shares_sold);
        }
    }
}
