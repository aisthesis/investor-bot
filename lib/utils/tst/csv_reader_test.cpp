/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * csv_reader_test.cpp
 *
 * tests for CsvReader class
 *
 * Author Marshall Farrier
 * Since 2014-09-10
 */

#include <string>
#include <vector>

#include "catch.hpp"

#include "csv_reader.h"
#include "globals.h"

TEST_CASE("get ohlc data", "[CsvReader]") {
    std::string path = "../tst_data/ohlc/";
    std::vector<DailyOhlcs> data;

    SECTION("well-formed test data") {
        SECTION("with header row") {
            std::vector<std::string> tickers = { "foo", "bar", "blah" };
            CsvReader reader(path, tickers);
            data = reader.get_ohlc_data();
            REQUIRE(data.size() == 6);
            
            // 1972-06-01
            REQUIRE(data[0].date == "1972-06-01");
            // foo
            REQUIRE(approx(data[0].ohlc_values["foo"].open, 4.7292));
            REQUIRE(approx(data[0].ohlc_values["foo"].high, 4.7392));
            REQUIRE(approx(data[0].ohlc_values["foo"].low, 4.6767));
            REQUIRE(approx(data[0].ohlc_values["foo"].close, 4.7083));
            // bar
            REQUIRE(approx(data[0].ohlc_values["bar"].open, 9.4583));
            REQUIRE(approx(data[0].ohlc_values["bar"].high, 9.5344));
            REQUIRE(approx(data[0].ohlc_values["bar"].low, 9.4444));
            REQUIRE(approx(data[0].ohlc_values["bar"].close, 9.5067));
            // blah
            REQUIRE(approx(data[0].ohlc_values["blah"].open, 2.1706));
            REQUIRE(approx(data[0].ohlc_values["blah"].high, 2.1735));
            REQUIRE(approx(data[0].ohlc_values["blah"].low, 2.1492));
            REQUIRE(approx(data[0].ohlc_values["blah"].close, 2.1534));

            // 1972-06-05 (only data is for blah)
            REQUIRE(data[2].date == "1972-06-05");
            REQUIRE(approx(data[2].ohlc_values["blah"].open, 2.1492));
            REQUIRE(approx(data[2].ohlc_values["blah"].high, 2.1696));
            REQUIRE(approx(data[2].ohlc_values["blah"].low, 2.1411));
            REQUIRE(approx(data[2].ohlc_values["blah"].close, 2.1492));

            // 1973-01-02 (data for foo and bar only)
            REQUIRE(data[4].date == "1973-01-02");
            // foo
            REQUIRE(approx(data[4].ohlc_values["foo"].open, 5.5417));
            REQUIRE(approx(data[4].ohlc_values["foo"].high, 5.6567));
            REQUIRE(approx(data[4].ohlc_values["foo"].low, 5.5317));
            REQUIRE(approx(data[4].ohlc_values["foo"].close, 5.6250));
            // bar
            REQUIRE(approx(data[4].ohlc_values["bar"].open, 9.9583));
            REQUIRE(approx(data[4].ohlc_values["bar"].high, 10.1111));
            REQUIRE(approx(data[4].ohlc_values["bar"].low, 9.9583));
            REQUIRE(approx(data[4].ohlc_values["bar"].close, 10.1111));

        }
        SECTION("no header row") {
        }
    }

    SECTION("exceptions") {
        SECTION("file not found") {
            std::vector<std::string> tickers = { "zorg" };
            CsvReader reader(path, tickers);
            REQUIRE_THROWS_AS(data = reader.get_ohlc_data(), std::logic_error);
        }
        SECTION("bad data") {
            std::vector<std::string> tickers = { "evil" };
            CsvReader reader(path, tickers);
        }
    }
}
