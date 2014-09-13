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

#include "globals.h"
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

TEST_CASE("annual mult", "[Finance]") {
    constexpr double kLocalEpsilon = 0.00005;

    REQUIRE(approx(Finance::annual_mult("2001-01-01", 1.0, "2005-01-01", 16.0), 2.0));
    REQUIRE(approx(Finance::annual_mult("2001-01-01", 16.0, "2005-01-01", 1.0), 0.5));
    // actual S&P values
    REQUIRE(approx(Finance::annual_mult("1962-01-02", 70.96, "2014-04-09", 1872.18), 1.0646, kLocalEpsilon));
    REQUIRE(approx(Finance::annual_mult("1950-01-03", 16.66, "2014-04-25", 1863.4), 1.0761, kLocalEpsilon));
    // actual DJI
    REQUIRE(approx(Finance::annual_mult("1962-01-02", 724.71, "2014-04-09", 16437.18), 1.0615, kLocalEpsilon));
    
}

TEST_CASE("annual pct return", "[Finance]") {
    constexpr double kLocalEpsilon = 0.2;

    REQUIRE(approx(Finance::annual_pct_return("2001-01-01", 1.0, "2005-01-01", 16.0), 100.0));
    REQUIRE(approx(Finance::annual_pct_return("2001-01-01", 16.0, "2005-01-01", 1.0), -50.0));
    // actual S&P values
    REQUIRE(approx(Finance::annual_pct_return("1962-01-02", 70.96, "2014-04-09", 1872.18), 6.46, kLocalEpsilon));
    REQUIRE(approx(Finance::annual_pct_return("1950-01-03", 16.66, "2014-04-25", 1863.4), 7.61, kLocalEpsilon));
    // actual DJI
    REQUIRE(approx(Finance::annual_pct_return("1962-01-02", 724.71, "2014-04-09", 16437.18), 6.15, kLocalEpsilon));
    // other examples calculated in Excel
    REQUIRE(approx(Finance::annual_pct_return("2011-10-03", 34.21, "2012-06-26", 41.98), 32.31, kLocalEpsilon));
    REQUIRE(approx(Finance::annual_pct_return("2009-03-01", 7.6, "2012-10-01", 17.95), 27.08, kLocalEpsilon));
    REQUIRE(approx(Finance::annual_pct_return("2011-11-25", 14.7, "2013-10-09", 23.57), 28.67, kLocalEpsilon));
    REQUIRE(approx(Finance::annual_pct_return("2013-11-14", 64.28, "2014-03-06", 58.24), -27.52, kLocalEpsilon));
}
