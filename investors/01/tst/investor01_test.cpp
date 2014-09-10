/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor01_test.cpp
 *
 * tests for investor implementation 01
 * Framework is Catch:
 * https://github.com/philsquared/Catch
 *
 * Author Marshall Farrier
 * Since 2014-08-29
 */

#include "catch.hpp"

#include <string>
#include <unordered_map>
#include <vector>

#include "investor01.h"
#include "order.h"
#include "globals.h"

TEST_CASE("correct orders generated from recommendations", "[Investor01]") {
    Investor01 investor;

    SECTION("initialization") {
        REQUIRE(investor.n_long_pos() == 0);
        REQUIRE(approx(investor.cash(), 0.0));
        REQUIRE(approx(investor.pending(), 0.0));
    }

    SECTION("pending (from superclass)") {
        double add_to_pending = 100.0;
        double pending = investor.add_to_pending(add_to_pending);
        REQUIRE(approx(investor.pending(), add_to_pending));
        REQUIRE(approx(pending, add_to_pending));
        investor.clear_pending();
        REQUIRE(approx(investor.pending(), 0.0));
    }

    SECTION("portfolio (from superclass)") {
        double deposit_amt = 1000.0,
            expected_cash = 0.0,
            purchase_price = 500.0,
            sale_price = 200.0;
        std::string ticker1 = "blah";
        int shares_bought = 25,
            shares_sold = 20;

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
    }

    SECTION("orders") {
        investor.deposit(1000.01);

        // recommend buying foo
        std::unordered_map<std::string, double> strengths({{"foo", 1.0}});
        TickerOhlcMap ohlc_map({{"foo", {0.0, 40.0, 1.0, 20.0}}});
        std::vector<Order> orders = investor.order(strengths, ohlc_map);

        SECTION("single recommendation, empty portfolio, nothing pending") {
            REQUIRE(orders.size() == 1);
            REQUIRE(orders[0] == Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 50, 20.0));
            REQUIRE(approx(investor.pending(), 1000.0));
        }

        // recommendation with order still pending but nothing to sell
        strengths.clear();
        ohlc_map.clear();
        strengths["bar"] = 1.0;
        ohlc_map["bar"] = {0.0, 100.0, 1.0, 50.0};
        orders = investor.order(strengths, ohlc_map);
        SECTION("orders empty because other order is still pending") {
            REQUIRE(orders.size() == 0);
            REQUIRE(approx(investor.pending(), 1000.0));
        }

        // buy foo to use up all but 0.01 of cash
        investor.buy("foo", 50, 1000.0);
        investor.clear_pending();
        // foo still a buy, bar also a buy (cf. above)
        strengths["foo"] = 1.0;
        ohlc_map["foo"] = {0.0, 60.0, 1.0, 30.0};
        orders = investor.order(strengths, ohlc_map);
        // here we should sell 1/2 of foo to buy bar (no order yet for bar)
        SECTION("orders with nothing pending but insufficient cash") {
            REQUIRE(orders.size() == 1);
            REQUIRE(orders[0] == Order(Order::Type::kSell, Order::Mode::kLimit, "foo", 25, 30.0));
            REQUIRE(approx(investor.pending(), 0.0));
            REQUIRE(approx(investor.cash(), 0.01));
        }

        // sell half of foo, total cash will now be 750.01, nothing pending
        investor.sell("foo", 25, 750.0);
        orders = investor.order(strengths, ohlc_map);
        SECTION("order with enough cash and 1 stock in portfolio") {
            REQUIRE(orders.size() == 1);
            REQUIRE(orders[0] == Order(Order::Type::kBuy, Order::Mode::kLimit, "bar", 15, 50.0));
            REQUIRE(approx(investor.pending(), 750.0));
            REQUIRE(approx(investor.cash(), 750.01));
        }

        // hold recommendations
        investor.clear_pending();
        strengths["foo"] = 0.5;
        strengths["bar"] = 0.5;
        orders = investor.order(strengths, ohlc_map);
        SECTION("hold recommendations") {
            REQUIRE(orders.size() == 0);
        }

        // sell recommendation
        strengths["foo"] = 0.1;
        orders = investor.order(strengths, ohlc_map);
        SECTION("sell recommendation") {
            REQUIRE(orders[0] == Order(Order::Type::kSell, Order::Mode::kLimit, "foo", 25, 30.0));
            REQUIRE(approx(investor.pending(), 0.0));
        }
    }
}
