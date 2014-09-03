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

TEST_CASE("correct orders generated from recommendations", "[Investor01]") {
    Investor01 investor;
    investor.portfolio()->deposit(1000.0);

    // recommend buying foo
    std::unordered_map<std::string, double> strengths({{"foo", 1.0}});
    std::unordered_map<std::string, double> price_table({{"foo", 20.0}});
    std::vector<Order> orders = investor.order(strengths, price_table);

    // single recommendation, empty portfolio, nothing pending
    REQUIRE(orders.size() == 1);
    REQUIRE(orders[0].type() == Order::Type::kBuy);
    REQUIRE(orders[0].mode() == Order::Mode::kLimit);
    REQUIRE(orders[0].ticker() == "foo");
    REQUIRE(orders[0].shares() >= 49);
    REQUIRE(orders[0].share_price() > 19.99);
    REQUIRE(orders[0].share_price() < 20.01);
    REQUIRE(investor.pending() > 980.0);

    // recommendation with order still pending
    strengths.clear();
    price_table.clear();
    strengths["bar"] = 1.0;
    price_table["bar"] = 50.0;
    orders = investor.order(strengths, price_table);
    // orders empty because other order is still pending
    REQUIRE(orders.size() == 0);
    REQUIRE(investor.pending() > 980.0);

    // recommendation with no cash
    // buy foo
    investor.portfolio()->buy("foo", 50, 1000.0);
    investor.clear_pending();
    // foo still a buy
    strengths["foo"] = 1.0;
    price_table["foo"] = 30.0;
    orders = investor.order(strengths, price_table);
    // here we sell 1/2 of foo to buy bar (no order yet for bar)
    REQUIRE(orders.size() == 1);
    REQUIRE(orders[0].type() == Order::Type::kSell);
    REQUIRE(orders[0].mode() == Order::Mode::kLimit);
    REQUIRE(orders[0].ticker() == "foo");
    REQUIRE(orders[0].shares() >= 24);
    REQUIRE(orders[0].shares() <= 26);
    REQUIRE(orders[0].share_price() > 29.99);
    REQUIRE(orders[0].share_price() < 30.01);
    REQUIRE(investor.pending() < 0.01);
    REQUIRE(investor.portfolio()->cash() < 0.01);
    REQUIRE(investor.portfolio()->cash() > -0.01);

    // sell half of foo
    investor.portfolio()->sell("foo", 25, 750.0);
    orders = investor.order(strengths, price_table);
    REQUIRE(orders.size() == 1);
    REQUIRE(orders[0].type() == Order::Type::kBuy);
    REQUIRE(orders[0].mode() == Order::Mode::kLimit);
    REQUIRE(orders[0].ticker() == "bar");
    REQUIRE(orders[0].shares() >= 14);
    REQUIRE(orders[0].shares() <= 16);
    REQUIRE(orders[0].share_price() > 49.99);
    REQUIRE(orders[0].share_price() < 50.01);
    REQUIRE(investor.pending() > 700.0);
    REQUIRE(investor.portfolio()->cash() < 750.01);
    REQUIRE(investor.portfolio()->cash() > 749.99);

    // hold recommendations
    investor.clear_pending();
    strengths["foo"] = 0.5;
    strengths["bar"] = 0.5;
    orders = investor.order(strengths, price_table);
    REQUIRE(orders.size() == 0);

    // sell recommendation
    strengths["foo"] = 0.1;
    orders = investor.order(strengths, price_table);
    REQUIRE(orders[0].type() == Order::Type::kSell);
    REQUIRE(orders[0].mode() == Order::Mode::kLimit);
    REQUIRE(orders[0].ticker() == "foo");
    REQUIRE(orders[0].shares() == 25);
    REQUIRE(orders[0].share_price() > 29.99);
    REQUIRE(orders[0].share_price() < 30.01);
    REQUIRE(investor.pending() < 0.01);
}
