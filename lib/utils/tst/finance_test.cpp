/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * finance_test.cpp
 *
 * Unit tests for Finance class
 * Framework is Catch:
 * https://github.com/philsquared/Catch
 *
 * Author Marshall Farrier
 * Since 2014-09-05
 */

#include "catch.hpp"

#include <string>

#include "finance.h"

TEST_CASE("date parsing", "[Finance]") {
    REQUIRE(Finance::year("1066-05-15") == 1066);
    REQUIRE(Finance::month("1066-05-15") == 5);
    REQUIRE(Finance::day_of_month("1066-05-15") == 15);
}

TEST_CASE("date difference", "[Finance]") {
    REQUIRE(Finance::date_diff("2011-04-01", "2011-04-02") == 1);
    REQUIRE(Finance::date_diff("2010-04-01", "2011-04-02") == 366);
    REQUIRE(Finance::date_diff("1902-03-05", "2059-12-24") == 57638);
    REQUIRE(Finance::date_diff("1902-01-05", "2059-12-24") == 57697);
    REQUIRE(Finance::date_diff("1902-03-05", "2059-01-24") == 57304);
    // 2 leap years
    REQUIRE(Finance::date_diff("1904-03-05", "2084-12-24") == 66039);
    REQUIRE(Finance::date_diff("1904-01-05", "2084-12-24") == 66099);
    REQUIRE(Finance::date_diff("1904-03-05", "2084-02-24") == 65735);
    REQUIRE(Finance::date_diff("1904-02-05", "2084-01-24") == 65733);
    REQUIRE(Finance::date_diff("2000-02-01", "2000-03-01") == 29);
    REQUIRE(Finance::date_diff("2000-02-01", "2004-02-01") == 1461);
    REQUIRE(Finance::date_diff("2000-02-01", "2004-03-01") == 1490);
    REQUIRE(Finance::date_diff("2000-03-01", "2004-03-01") == 1461);
    REQUIRE(Finance::date_diff("2000-03-01", "2004-02-01") == 1432);
}
