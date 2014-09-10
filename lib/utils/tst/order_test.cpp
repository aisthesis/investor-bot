/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order_test.cpp
 *
 * tests for Order class
 *
 * Author Marshall Farrier
 * Since 2014-08-27
 */

#include <string>
#include <ostream>

#include "catch.hpp"

#include "globals.h"
#include "order.h"

TEST_CASE("order tests", "[Order]") {
    std::string ticker = "blah";
    int shares = 5;
    double share_price = 3.14159;
    double low_mkt_price = 3.0;
    double lower_mkt_price = 2.9;
    double high_mkt_price = 3.15;
    double higher_mkt_price = 3.2;

    SECTION("buy order") {
        SECTION("limit buy order") {
            Order order(Order::Type::kBuy, Order::Mode::kLimit, ticker, shares, share_price);
            REQUIRE(order.type() == Order::Type::kBuy);
            REQUIRE(order.mode() == Order::Mode::kLimit);
            REQUIRE(order.ticker() == ticker);
            REQUIRE(order.shares() == shares);
            REQUIRE(approx(order.share_price(), share_price));
            REQUIRE(order == Order(Order::Type::kBuy, Order::Mode::kLimit, ticker, shares, share_price));
            REQUIRE(order != Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price));

            SECTION("fillable") {
                REQUIRE(order.fillable(low_mkt_price));
                REQUIRE(!order.fillable(high_mkt_price));
                REQUIRE(order.fillable(low_mkt_price, lower_mkt_price));
                REQUIRE(!order.fillable(high_mkt_price, higher_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, low_mkt_price));
            }
        }
        SECTION("stop-loss buy order") {
            Order order(Order::Type::kBuy, Order::Mode::kStopLoss, ticker, shares, share_price);
            REQUIRE(order == Order(Order::Type::kBuy, Order::Mode::kStopLoss, ticker, shares, share_price));
            REQUIRE(order != Order(Order::Type::kBuy, Order::Mode::kLimit, ticker, shares, share_price));

            SECTION("fillable") {
                REQUIRE(!order.fillable(low_mkt_price));
                REQUIRE(order.fillable(high_mkt_price));
                REQUIRE(!order.fillable(low_mkt_price, lower_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, higher_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, low_mkt_price));
            }
        }
        SECTION("market buy order") {
            Order order(Order::Type::kBuy, Order::Mode::kMarket, ticker, shares, share_price);
            REQUIRE(order == Order(Order::Type::kBuy, Order::Mode::kMarket, ticker, shares, share_price));
            REQUIRE(order != Order(Order::Type::kBuy, Order::Mode::kMarket, "notblah", shares, share_price));

            SECTION("fillable") {
                REQUIRE(order.fillable(low_mkt_price));
                REQUIRE(order.fillable(high_mkt_price));
                REQUIRE(order.fillable(low_mkt_price, lower_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, higher_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, low_mkt_price));
            }
        }
    }
    SECTION("sell order") {
        SECTION("limit sell order") {
            Order order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price);
            REQUIRE(order == Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price));
            REQUIRE(order != Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares + 1, share_price));

            SECTION("fillable") {
                REQUIRE(!order.fillable(low_mkt_price));
                REQUIRE(order.fillable(high_mkt_price));
                REQUIRE(!order.fillable(low_mkt_price, lower_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, higher_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, low_mkt_price));
            }
        }
        SECTION("stop-loss sell order") {
            Order order(Order::Type::kSell, Order::Mode::kStopLoss, ticker, shares, share_price);
            REQUIRE(order == Order(Order::Type::kSell, Order::Mode::kStopLoss, ticker, shares, share_price));
            REQUIRE(order != Order(Order::Type::kSell, Order::Mode::kStopLoss, ticker, shares, share_price + 2.0));

            SECTION("fillable") {
                REQUIRE(order.fillable(low_mkt_price));
                REQUIRE(!order.fillable(high_mkt_price));
                REQUIRE(order.fillable(low_mkt_price, lower_mkt_price));
                REQUIRE(!order.fillable(high_mkt_price, higher_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, low_mkt_price));
            }
        }
        SECTION("market sell order") {
            Order order(Order::Type::kSell, Order::Mode::kMarket, ticker, shares, share_price);
            REQUIRE(order == Order(Order::Type::kSell, Order::Mode::kMarket, ticker, shares, share_price));
            REQUIRE(order != Order(Order::Type::kSell, Order::Mode::kLimit, ticker, shares, share_price));

            SECTION("fillable") {
                REQUIRE(order.fillable(low_mkt_price));
                REQUIRE(order.fillable(high_mkt_price));
                REQUIRE(order.fillable(low_mkt_price, lower_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, higher_mkt_price));
                REQUIRE(order.fillable(high_mkt_price, low_mkt_price));
            }
        }
    }
}

TEST_CASE("serialization", "[Order]") {
    std::ostringstream oss;

    SECTION("order type") {
        SECTION("buy") {
            oss << Order::Type::kBuy;
            REQUIRE(oss.str() == "buy");
        }
        SECTION("sell") {
            oss << Order::Type::kSell;
            REQUIRE(oss.str() == "sell");
        }
    }

    SECTION("order mode") {
        SECTION("limit") {
            oss << Order::Mode::kLimit;
            REQUIRE(oss.str() == "limit");
        }
        SECTION("market") {
            oss << Order::Mode::kMarket;
            REQUIRE(oss.str() == "market");
        }
        SECTION("stop-loss") {
            oss << Order::Mode::kStopLoss;
            REQUIRE(oss.str() == "stop-loss");
        }
    }

    SECTION("complete order") {
        SECTION("limit buy order") {
            oss << Order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 3, 0);
            REQUIRE(oss.str() == "buy 3 shares foo at limit 0.00");
        }

        SECTION("stop-loss sell order") {
            oss << Order(Order::Type::kSell, Order::Mode::kStopLoss, "bar", 100001, 3.14159265358);
            REQUIRE(oss.str() == "sell 100001 shares bar at stop-loss 3.14");
        }

        SECTION("market buy order") {
            oss << Order(Order::Type::kBuy, Order::Mode::kMarket, "foo", 123, 1234567.899);
            REQUIRE(oss.str() == "buy 123 shares foo at market 1234567.90");
        }
    }
}
