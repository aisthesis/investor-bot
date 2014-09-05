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

#include "globals.h"
#include "investor.h"
#include "simulator.h"

// concrete subclass for testing
class MyInvestor : public Investor {
    std::vector<Order> order(const std::unordered_map<std::string, double> &strengths,
            const std::unordered_map<std::string, double> &price_list) {
        return std::vector<Order>();
    }
};

constexpr double kEpsilon = 0.001;

TEST_CASE("correct initialization", "[Simulator]") {
    MyInvestor investor;
    std::vector<DailyOhlcs> price_data;
    std::vector<DailyRecommendations> recommendations;
    Simulator simulator(investor, price_data, recommendations);

    REQUIRE(simulator.actions().size() == 0);
    REQUIRE(simulator.start_value() > -kEpsilon);
    REQUIRE(simulator.start_value() < kEpsilon);
    REQUIRE(simulator.end_value() > -kEpsilon);
    REQUIRE(simulator.end_value() < kEpsilon);
    REQUIRE(simulator.start_date() == "");
    REQUIRE(simulator.end_date() == "");
}
