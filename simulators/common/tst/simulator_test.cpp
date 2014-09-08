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
#include <stdexcept>

#include "globals.h"
#include "investor.h"
#include "investor01.h"
#include "simulator.h"
#include "order_action.h"

constexpr double kInitialDeposit = 1000.0;

TEST_CASE("correct initialization", "[Simulator]") {
    Investor01 investor;
    investor.deposit(kInitialDeposit);
    std::vector<DailyOhlcs> ohlc_data;
    std::vector<DailyRecommendations> recommendations;
    Simulator simulator(investor, ohlc_data, recommendations);

    REQUIRE(simulator.actions().size() == 0);
    REQUIRE(simulator.start_value() > -kEpsilon);
    REQUIRE(simulator.start_value() < kEpsilon);
    REQUIRE(simulator.end_value() > -kEpsilon);
    REQUIRE(simulator.end_value() < kEpsilon);
    REQUIRE(simulator.start_date() == "");
    REQUIRE(simulator.end_date() == "");
}

TEST_CASE("errors in data inputs", "[Simulator]") {
    Investor01 investor;
    investor.deposit(kInitialDeposit);
    std::vector<DailyOhlcs> ohlc_data;
    std::vector<DailyRecommendations> recommendations;

    SECTION("no recommendations") {
        ohlc_data.push_back({"2014-01-01", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
        Simulator simulator(investor, ohlc_data, recommendations);
        REQUIRE_THROWS_AS(simulator.run(), std::logic_error);
    }

    SECTION("no ohlc data") {
        recommendations.push_back({"2014-01-01", {{"foo", 1.0}}});
        Simulator simulator(investor, ohlc_data, recommendations);
        REQUIRE_THROWS_AS(simulator.run(), std::logic_error);
    }

    SECTION("gap in ohlc data") {
        ohlc_data.push_back({"2014-01-01", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
        recommendations.push_back({"2014-01-01", {{"foo", 1.0}}});
        ohlc_data.push_back({"2014-01-03", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
        recommendations.push_back({"2014-01-02", {{"foo", 1.0}}});
        Simulator simulator(investor, ohlc_data, recommendations);
        REQUIRE_THROWS_AS(simulator.run(), std::logic_error);
    }

    SECTION("gap in recommendations") {
        ohlc_data.push_back({"2014-01-01", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
        recommendations.push_back({"2014-01-01", {{"foo", 1.0}}});
        ohlc_data.push_back({"2014-01-02", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
        recommendations.push_back({"2014-01-03", {{"foo", 1.0}}});
        Simulator simulator(investor, ohlc_data, recommendations);
        REQUIRE_THROWS_AS(simulator.run(), std::logic_error);
    }
}

TEST_CASE("correct orders and growth", "[Simulator]") {
    Investor01 investor;
    investor.deposit(kInitialDeposit);
    double expected_end_value = kInitialDeposit;
    std::vector<DailyOhlcs> ohlc_data;
    std::vector<DailyRecommendations> recommendations;
    ohlc_data.push_back({"2013-12-31", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
    ohlc_data.push_back({"2014-01-01", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
    // should generate buy order for 400 shares of foo at 2.5
    recommendations.push_back({"2014-01-01", {{"foo", 1.0}}});
    // order can be filled
    ohlc_data.push_back({"2014-01-02", {{"foo", {2.0, 1.0, 3.1, 3.0}}}});
    expected_end_value = 3.0 * 400;
    // recommend selling foo
    recommendations.push_back({"2014-01-02", {{"foo", 0.0}}});
    // order can be filled
    ohlc_data.push_back({"2014-01-03", {{"foo", {2.0, 1.0, 3.1, 2.5}}}});
    // expected end value unchanged: 1200.0

    Simulator simulator(investor, ohlc_data, recommendations);
    simulator.run();
    std::vector<OrderAction> actions = simulator.actions();
    REQUIRE(simulator.start_value() > kInitialDeposit - kEpsilon);
    REQUIRE(simulator.start_value() < kInitialDeposit + kEpsilon);
    // correct actions
    REQUIRE(actions[0].date() == "2014-01-01");
    REQUIRE(actions[0].act() == OrderAction::Act::kPlace);
    REQUIRE(actions[0].order().type() == Order::Type::kBuy);
    REQUIRE(actions[0].order().mode() == Order::Mode::kLimit);
    REQUIRE(actions[0].order().ticker() == "foo");
    REQUIRE(actions[0].order().shares() == 400);
    REQUIRE(actions[0].order().share_price() > 2.5 - kEpsilon);
    REQUIRE(actions[0].order().share_price() < 2.5 + kEpsilon);
    REQUIRE(actions[0].total() > -kEpsilon);
    REQUIRE(actions[0].total() < kEpsilon);
    REQUIRE(actions[0] == OrderAction("2014-01-01", OrderAction::Act::kPlace, Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5), 0.0));
    REQUIRE(simulator.end_value() > expected_end_value - kEpsilon);
    REQUIRE(simulator.end_value() < expected_end_value + kEpsilon);
    
}
