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

#include "simulator.h"

TEST_CASE("correct initialization", "[Simulator]") {
    Simulator simulator;
}
