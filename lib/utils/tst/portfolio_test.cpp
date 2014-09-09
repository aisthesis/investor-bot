/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * portfolio_test.cpp
 *
 * tests for Portfolio class
 *
 * Author Marshall Farrier
 * Since 2014-08-25
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "catch.hpp"

#include "portfolio.h"
#include "globals.h"

TEST_CASE("portfolio tests", "[Portfolio]") {
    int shares1 = 0,
        shares2 = 0,
        shares3 = 0;
    std::string eq1 = "foo",
        eq2 = "bar",
        eq3 = "blah";
    std::unordered_map<std::string, double> price_table;
    std::unordered_map<std::string, Ohlc> ohlc_table;
    price_table[eq1] = 10.0;
    price_table[eq2] = 5.0;
    ohlc_table[eq1] = { 0.0, 20.0, 1.0, 10.0 };
    ohlc_table[eq2] = { 0.0, 20.0, 1.0, 5.0 };

    SECTION("default constructor") {
        Portfolio portfolio;
        double expected_cash = 0.0,
            expected_value = 0.0;

        SECTION("initial state") {
            REQUIRE(approx(expected_cash, portfolio.cash()));
            REQUIRE(shares1 == portfolio.shares(eq1));
            REQUIRE(shares2 == portfolio.shares(eq2));
            REQUIRE(portfolio.n_long_pos() == 0);
            REQUIRE(portfolio.n_short_pos() == 0);
            REQUIRE(portfolio.value(price_table) == expected_value);
            REQUIRE(portfolio.value(ohlc_table) == expected_value);
        }
        SECTION("buy and sell shares") {
            // buy 50 shares of eq1 for 200.0
            portfolio.buy(eq1, 50, 200.0);
            expected_cash -= 200.0;
            shares1 += 50;
            // the shares are worth 500.0, so value is increased by 300.0
            expected_value += 300.0;
            REQUIRE(approx(portfolio.cash(), expected_cash));
            REQUIRE(shares1 == portfolio.shares(eq1));
            REQUIRE(approx(portfolio.value(price_table), expected_value));
            REQUIRE(approx(portfolio.value(ohlc_table), expected_value));
            // sell 20 shares of eq1 and eq2 for 400.0 
            portfolio.sell(eq1, 20, 400.0);
            // shares are worth 200.0 but sold for 400.0, so value increases by 200.0
            expected_value += 200.0;
            expected_cash += 400.0;
            shares1 -= 20;  // 30 altogether
            portfolio.sell(eq2, 20, 400.0);
            shares2 -= 20;  // -20 (short)
            // shares are worth 100.0 but sold for 400.0
            expected_value += 300.0;
            expected_cash += 400.0;
            REQUIRE(approx(portfolio.value(ohlc_table), expected_value));
            portfolio.sell(eq3, 10, 10.0);
            shares3 -= 10;  // -10 (short)
            expected_cash += 10.0;
            REQUIRE(portfolio.shares(eq1) == shares1);
            REQUIRE(portfolio.shares(eq2) == shares2);
            REQUIRE(approx(portfolio.cash(), expected_cash));
            REQUIRE(portfolio.n_long_pos() == 1);
            REQUIRE(portfolio.n_short_pos() == 2);
            SECTION("iterator") {
                std::unordered_map<std::string, int>::iterator it = std::find_if(portfolio.begin(),
                        portfolio.end(), [&](std::pair<std::string, int> my_pair) { return my_pair.first == eq1; });
                REQUIRE(it->second == shares1);
                it = std::find_if(portfolio.begin(), portfolio.end(), 
                        [&](std::pair<std::string, int> my_pair) { return my_pair.first == eq2; });
                REQUIRE(it->second == shares2);
                it = std::find_if(portfolio.begin(), portfolio.end(), 
                        [&](std::pair<std::string, int> my_pair) { return my_pair.first == eq3; });
                REQUIRE(it->second == shares3);
            }
            SECTION("exceptions") {
                // selling eq3 causes exception in checking value (equity not in ohlc or price table)
                REQUIRE_THROWS_AS(portfolio.value(price_table), std::invalid_argument);
                REQUIRE_THROWS_AS(portfolio.value(ohlc_table), std::invalid_argument);
                // pass negative cost or shares to buy or sell
                REQUIRE_THROWS_AS(portfolio.buy(eq1, 10, -3.0), std::invalid_argument);
                REQUIRE_THROWS_AS(portfolio.buy(eq1, -10, 3.0), std::invalid_argument);
                REQUIRE_THROWS_AS(portfolio.sell(eq1, 10, -3.0), std::invalid_argument);
                REQUIRE_THROWS_AS(portfolio.sell(eq1, -10, 3.0), std::invalid_argument);
            }
        }
    }
    SECTION("Portfolio(const double &)") {
        Portfolio portfolio(1000.0);
        double expected_cash = 1000.0,
            expected_value = 1000.0;

        SECTION("initial state") {
            REQUIRE(approx(expected_cash, portfolio.cash()));
            REQUIRE(shares1 == portfolio.shares(eq1));
            REQUIRE(shares2 == portfolio.shares(eq2));
            REQUIRE(portfolio.n_long_pos() == 0);
            REQUIRE(portfolio.n_short_pos() == 0);
            REQUIRE(portfolio.value(price_table) == expected_value);
            REQUIRE(portfolio.value(ohlc_table) == expected_value);
        }
        SECTION("buy shares") {
            // buy 50 shares of eq1 for 200.0
            portfolio.buy(eq1, 50, 200.0);
            expected_cash -= 200.0;
            shares1 += 50;
            // the shares are worth 500.0, so value is increased by 300.0
            expected_value += 300.0;
            REQUIRE(approx(portfolio.cash(), expected_cash));
            REQUIRE(shares1 == portfolio.shares(eq1));
            REQUIRE(approx(portfolio.value(price_table), expected_value));
            REQUIRE(approx(portfolio.value(ohlc_table), expected_value));
        }
    }
}
