/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * order_action_test.cpp
 *
 * Unit tests for OrderAction class
 * Framework is Catch:
 * https://github.com/philsquared/Catch
 *
 * Author Marshall Farrier
 * Since 2014-09-05
 */

#include "catch.hpp"

#include <string>
#include <ostream>

#include "order_action.h"
#include "order.h"
#include "globals.h"

TEST_CASE("place order", "[OrderAction]") {
    OrderAction action("2014-09-03", OrderAction::Act::kPlace, 
            Order(Order::Type::kBuy, Order::Mode::kMarket, "foo", 3, 6.0));
    
    REQUIRE(action.date() == "2014-09-03");
    REQUIRE(action.act() == OrderAction::Act::kPlace);
    REQUIRE(action.order().type() == Order::Type::kBuy);
    REQUIRE(action.order().mode() == Order::Mode::kMarket);
    REQUIRE(action.order().ticker() == "foo");
    REQUIRE(action.order().shares() == 3);
    REQUIRE(approx(action.order().share_price(), 6.0));
    REQUIRE(approx(action.total(), 0.0));
    REQUIRE(action == OrderAction("2014-09-03", OrderAction::Act::kPlace,
            Order(Order::Type::kBuy, Order::Mode::kMarket, "foo", 3, 6.0)));
    REQUIRE(action != OrderAction("2014-09-04", OrderAction::Act::kPlace,
            Order(Order::Type::kBuy, Order::Mode::kMarket, "foo", 3, 6.0)));

}

TEST_CASE("fill order", "[OrderAction]") {
    OrderAction action("2014-09-03", OrderAction::Act::kFill, 
            Order(Order::Type::kSell, Order::Mode::kLimit, "bar", 10, 6.0), 65.0);
    
    REQUIRE(action.date() == "2014-09-03");
    REQUIRE(action.act() == OrderAction::Act::kFill);
    REQUIRE(action.order().type() == Order::Type::kSell);
    REQUIRE(action.order().mode() == Order::Mode::kLimit);
    REQUIRE(action.order().ticker() == "bar");
    REQUIRE(action.order().shares() == 10);
    REQUIRE(approx(action.order().share_price(), 6.0));
    REQUIRE(approx(action.total(), 65.0));
    REQUIRE(action == OrderAction("2014-09-03", OrderAction::Act::kFill,
            Order(Order::Type::kSell, Order::Mode::kLimit, "bar", 10, 6.0), 65.0));
    REQUIRE(action != OrderAction("2014-09-03", OrderAction::Act::kPlace,
            Order(Order::Type::kSell, Order::Mode::kLimit, "bar", 10, 6.0), 65.0));
}

TEST_CASE("cancel order", "[OrderAction]") {
    OrderAction action("2014-09-03", OrderAction::Act::kCancel, 
            Order(Order::Type::kSell, Order::Mode::kLimit, "bar", 10, 6.0));
    
    REQUIRE(action.date() == "2014-09-03");
    REQUIRE(action.act() == OrderAction::Act::kCancel);
    REQUIRE(action.order().type() == Order::Type::kSell);
    REQUIRE(action.order().mode() == Order::Mode::kLimit);
    REQUIRE(action.order().ticker() == "bar");
    REQUIRE(action.order().shares() == 10);
    REQUIRE(approx(action.order().share_price(), 6.0));
    REQUIRE(approx(action.total(), 0.0));
    REQUIRE(action == OrderAction("2014-09-03", OrderAction::Act::kCancel,
            Order(Order::Type::kSell, Order::Mode::kLimit, "bar", 10, 6.0)));
    REQUIRE(action != OrderAction("2014-09-03", OrderAction::Act::kCancel,
            Order(Order::Type::kBuy, Order::Mode::kLimit, "bar", 10, 6.0)));
    REQUIRE(action != OrderAction("2014-09-03", OrderAction::Act::kCancel,
            Order(Order::Type::kSell, Order::Mode::kLimit, "bar", 10, 6.0), 1.0));
}

TEST_CASE("serialization", "[OrderAction]") {
    std::ostringstream oss;

    SECTION("act") {
        SECTION("place") {
            oss << OrderAction::Act::kPlace;
            REQUIRE(oss.str() == "place");
        }
        SECTION("fill") {
            oss << OrderAction::Act::kFill;
            REQUIRE(oss.str() == "fill");
        }
        SECTION("cancel") {
            oss << OrderAction::Act::kCancel;
            REQUIRE(oss.str() == "cancel");
        }
    }

    SECTION("complete action") {
        Order order(Order::Type::kBuy, Order::Mode::kLimit, "foo", 3, 7.2296);
        SECTION("place") {
            oss << OrderAction("2014-08-01", OrderAction::Act::kPlace, order);
            REQUIRE(oss.str() == "2014-08-01 place for 0.00 {buy 3 shares foo at limit 7.23}");
        }
        SECTION("fill") {
            oss << OrderAction("1932-01-31", OrderAction::Act::kFill, order, 30.056);
            REQUIRE(oss.str() == "1932-01-31 fill for 30.06 {buy 3 shares foo at limit 7.23}");
        }
        SECTION("cancel") {
            oss << OrderAction("1945-05-31", OrderAction::Act::kCancel, order);
            REQUIRE(oss.str() == "1945-05-31 cancel for 0.00 {buy 3 shares foo at limit 7.23}");
        }
    }
}
