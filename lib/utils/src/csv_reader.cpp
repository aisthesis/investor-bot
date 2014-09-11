/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * csv_reader.cpp
 *
 * Reads csv files and generates output in desired data format.
 * Throw logic_error exception if data in file cannot be translated
 * into the desired output format.
 *
 * Author Marshall Farrier
 * Since 2014-09-10
 */

#include <string>
#include <iterator>
#include <vector>

#include "csv_reader.h"
#include "globals.h"

CsvReader::CsvReader(const std::string &path, const std::vector<std::string> &fnames,
        const bool &has_header_row)
        : path_(path), fnames_(fnames), has_header_row_(has_header_row) {}

std::vector<DailyOhlcs> CsvReader::get_ohlc_data() const {
    return std::vector<DailyOhlcs>();
}

std::vector<DailyRecommendations> CsvReader::get_recommendations() const {
    return std::vector<DailyRecommendations>();
}
