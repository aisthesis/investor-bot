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
    std::string path = "../data/";
    std::vector<std::string> fnames = { "foo.csv", "bar.csv", "blah.csv" };

    CsvReader reader(path, fnames);
}
