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
#include <stdexcept>

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
            std::vector<std::string> tickers = { "foo", "bar", "blah" };
            std::string suffix = "-noheader.csv";
            CsvReader reader(path, tickers, suffix, false);
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
            REQUIRE_THROWS_AS(data = reader.get_ohlc_data(), std::invalid_argument);
        }
    }
}

TEST_CASE("get recommendations", "[CsvReader]") {
    std::string path = "../tst_data/rec/";
    std::vector<DailyRecommendations> data;

    SECTION("well-formed test data") {
        SECTION("with header row") {
            std::vector<std::string> tickers = { "foo", "bar", "blah" };
            CsvReader reader(path, tickers);
            data = reader.get_recommendations();
            REQUIRE(data.size() == 8);
            
            // 2010-12-30
            REQUIRE(data[0].date == "2010-12-30");
            REQUIRE(approx(data[0].recommendations["foo"], 1.0));
            REQUIRE(approx(data[0].recommendations["blah"], 0.0));

            // 2010-12-31
            REQUIRE(data[1].date == "2010-12-31");
            REQUIRE(approx(data[1].recommendations["foo"], 1.0));
            REQUIRE(approx(data[1].recommendations["bar"], 0.123));
            REQUIRE_THROWS_AS(data[1].recommendations.at("blah"), std::out_of_range);

            // 2011-01-03
            REQUIRE(data[2].date == "2011-01-03");
            REQUIRE(approx(data[2].recommendations["foo"], 0.0));
            REQUIRE(approx(data[2].recommendations["blah"], 1.0));
            REQUIRE_THROWS_AS(data[2].recommendations.at("bar"), std::out_of_range);

            // 2011-01-04
            REQUIRE(data[3].date == "2011-01-04");
            REQUIRE(approx(data[3].recommendations["foo"], 1.0));
            REQUIRE(approx(data[3].recommendations["bar"], 0.5781));
            REQUIRE_THROWS_AS(data[3].recommendations.at("blah"), std::out_of_range);

            // 2011-01-05
            REQUIRE(data[4].date == "2011-01-05");
            REQUIRE(approx(data[4].recommendations["foo"], 0.0));
            REQUIRE(approx(data[4].recommendations["blah"], 1.0));
            REQUIRE_THROWS_AS(data[4].recommendations.at("bar"), std::out_of_range);

            // 2011-01-06
            REQUIRE(data[5].date == "2011-01-06");
            REQUIRE(approx(data[5].recommendations["foo"], 1.0));
            REQUIRE(approx(data[5].recommendations["bar"], 1.0));
            REQUIRE_THROWS_AS(data[5].recommendations.at("blah"), std::out_of_range);

            // 2011-01-07
            REQUIRE(data[6].date == "2011-01-07");
            REQUIRE(approx(data[6].recommendations["foo"], 0.0));
            REQUIRE(approx(data[6].recommendations["blah"], 0.1456));
            REQUIRE_THROWS_AS(data[6].recommendations.at("bar"), std::out_of_range);

            // 2011-01-10
            REQUIRE(data[7].date == "2011-01-10");
            REQUIRE(approx(data[7].recommendations["blah"], 0.333));
            REQUIRE_THROWS_AS(data[7].recommendations.at("foo"), std::out_of_range);
            REQUIRE_THROWS_AS(data[7].recommendations.at("bar"), std::out_of_range);
        }
        SECTION("no header row") {
            std::vector<std::string> tickers = { "foo", "bar", "blah" };
            std::string suffix = "-noheader.csv";
            CsvReader reader(path, tickers, suffix, false);
            data = reader.get_recommendations();
            REQUIRE(data.size() == 8);
            
            // 2010-12-30
            REQUIRE(data[0].date == "2010-12-30");
            REQUIRE(approx(data[0].recommendations["foo"], 1.0));
            REQUIRE(approx(data[0].recommendations["blah"], 0.0));

            // 2010-12-31
            REQUIRE(data[1].date == "2010-12-31");
            REQUIRE(approx(data[1].recommendations["foo"], 1.0));
            REQUIRE(approx(data[1].recommendations["bar"], 0.123));
            REQUIRE_THROWS_AS(data[1].recommendations.at("blah"), std::out_of_range);

            // 2011-01-03
            REQUIRE(data[2].date == "2011-01-03");
            REQUIRE(approx(data[2].recommendations["foo"], 0.0));
            REQUIRE(approx(data[2].recommendations["blah"], 1.0));
            REQUIRE_THROWS_AS(data[2].recommendations.at("bar"), std::out_of_range);

            // 2011-01-04
            REQUIRE(data[3].date == "2011-01-04");
            REQUIRE(approx(data[3].recommendations["foo"], 1.0));
            REQUIRE(approx(data[3].recommendations["bar"], 0.5781));
            REQUIRE_THROWS_AS(data[3].recommendations.at("blah"), std::out_of_range);

            // 2011-01-05
            REQUIRE(data[4].date == "2011-01-05");
            REQUIRE(approx(data[4].recommendations["foo"], 0.0));
            REQUIRE(approx(data[4].recommendations["blah"], 1.0));
            REQUIRE_THROWS_AS(data[4].recommendations.at("bar"), std::out_of_range);

            // 2011-01-06
            REQUIRE(data[5].date == "2011-01-06");
            REQUIRE(approx(data[5].recommendations["foo"], 1.0));
            REQUIRE(approx(data[5].recommendations["bar"], 1.0));
            REQUIRE_THROWS_AS(data[5].recommendations.at("blah"), std::out_of_range);

            // 2011-01-07
            REQUIRE(data[6].date == "2011-01-07");
            REQUIRE(approx(data[6].recommendations["foo"], 0.0));
            REQUIRE(approx(data[6].recommendations["blah"], 0.1456));
            REQUIRE_THROWS_AS(data[6].recommendations.at("bar"), std::out_of_range);

            // 2011-01-10
            REQUIRE(data[7].date == "2011-01-10");
            REQUIRE(approx(data[7].recommendations["blah"], 0.333));
            REQUIRE_THROWS_AS(data[7].recommendations.at("foo"), std::out_of_range);
            REQUIRE_THROWS_AS(data[7].recommendations.at("bar"), std::out_of_range);
        }
    }

    SECTION("exceptions") {
        SECTION("file not found") {
            std::vector<std::string> tickers = { "zorg" };
            CsvReader reader(path, tickers);
            REQUIRE_THROWS_AS(data = reader.get_recommendations(), std::logic_error);
        }
        SECTION("bad data") {
            std::vector<std::string> tickers = { "evil" };
            CsvReader reader(path, tickers);
            REQUIRE_THROWS_AS(data = reader.get_recommendations(), std::invalid_argument);
        }
    }
}
