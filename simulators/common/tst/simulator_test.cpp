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
    REQUIRE(approx(simulator.start_value(), 0.0));
    REQUIRE(approx(simulator.end_value(), 0.0));
    REQUIRE(simulator.start_date() == "");
    REQUIRE(simulator.end_date() == "");
    REQUIRE(approx(investor.pending(), 0.0));
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

TEST_CASE("fillable buy and sell", "[Simulator]") {
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
    REQUIRE(approx(simulator.start_value(), kInitialDeposit));
    // correct actions
    // placed buy order: use entire bankroll to buy foo
    REQUIRE(actions.size() == 4);
    REQUIRE(actions[0] == OrderAction("2014-01-01", OrderAction::Act::kPlace,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5)));
    // order to buy foo for 1000.0 filled
    REQUIRE(actions[1] == OrderAction("2014-01-02", OrderAction::Act::kFill,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5), -kInitialDeposit));
    // placed sell order
    REQUIRE(actions[2] == OrderAction("2014-01-02", OrderAction::Act::kPlace,
            Order(Order::Type::kSell, Order::Mode::kLimit, "foo", 400, 3.0)));
    // filled sell order
    REQUIRE(actions[3] == OrderAction("2014-01-03", OrderAction::Act::kFill,
            Order(Order::Type::kSell, Order::Mode::kLimit, "foo", 400, 3.0), 1200.0));

    REQUIRE(approx(simulator.end_value(), expected_end_value));
    // no orders pending after simulation
    REQUIRE(approx(investor.pending(), 0.0));
}

TEST_CASE("sell required for buy", "[Simulator]") {
    Investor01 investor;
    investor.deposit(kInitialDeposit);
    double expected_end_value = kInitialDeposit;
    std::vector<DailyOhlcs> ohlc_data;
    std::vector<DailyRecommendations> recommendations;
    ohlc_data.push_back({"2014-01-01", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
    // should generate buy order for 400 shares of foo at 2.5
    recommendations.push_back({"2014-01-01", {{"foo", 1.0}}});
    // order can be filled
    ohlc_data.push_back({"2014-01-02", {{"foo", {2.0, 1.0, 3.1, 3.0}},
            {"bar", {20.0, 10.0, 31.0, 25.0}}}});
    // recommend holding foo and buying bar
    recommendations.push_back({"2014-01-02", {{"foo", 0.5}, {"bar", 1.0}}}); 
    expected_end_value = 3.0 * 400;

    Simulator simulator(investor, ohlc_data, recommendations);
    simulator.run();
    std::vector<OrderAction> actions = simulator.actions();
    // actions[0] and actions[1] are same as above
    REQUIRE(actions.size() == 3);
    REQUIRE(actions[0] == OrderAction("2014-01-01", OrderAction::Act::kPlace,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5)));
    // order to buy foo for 1000.0 filled
    REQUIRE(actions[1] == OrderAction("2014-01-02", OrderAction::Act::kFill,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5), -kInitialDeposit));
    // placed sell order
    REQUIRE(actions[2] == OrderAction("2014-01-02", OrderAction::Act::kPlace,
            Order(Order::Type::kSell, Order::Mode::kLimit, "foo", 200, 3.0)));

    REQUIRE(approx(simulator.end_value(), expected_end_value));
    // no orders pending after simulation
    REQUIRE(approx(investor.pending(), 0.0));
}

TEST_CASE("buy can't be filled: price out of range", "[Simulator]") {
    Investor01 investor;
    investor.deposit(kInitialDeposit);
    double expected_end_value = kInitialDeposit;
    std::vector<DailyOhlcs> ohlc_data;
    std::vector<DailyRecommendations> recommendations;
    ohlc_data.push_back({"2014-01-01", {{"foo", {2.0, 1.0, 3.0, 2.5}}}});
    // should generate buy order for 400 shares of foo at 2.5
    recommendations.push_back({"2014-01-01", {{"foo", 1.0}}});
    // order can't be filled
    ohlc_data.push_back({"2014-01-02", {{"foo", {3.0, 2.6, 5.2, 4.0}}}});
    // continue to recommend buy
    recommendations.push_back({"2014-01-02", {{"foo", 1.0}}});

    Simulator simulator(investor, ohlc_data, recommendations);
    simulator.run();
    std::vector<OrderAction> actions = simulator.actions();

    REQUIRE(actions.size() == 3);
    // order placed
    REQUIRE(actions[0] == OrderAction("2014-01-01", OrderAction::Act::kPlace,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5)));
    // order canceled
    REQUIRE(actions[1] == OrderAction("2014-01-02", OrderAction::Act::kCancel,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 400, 2.5)));
    // end value unchanged
    REQUIRE(approx(simulator.end_value(), expected_end_value));
    // order for foo still pending after simulation
    REQUIRE(approx(investor.pending(), kInitialDeposit));
}
