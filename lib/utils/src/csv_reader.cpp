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
#include <vector>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <sstream>
#include <algorithm>

#include "csv_reader.h"
#include "globals.h"

CsvReader::CsvReader(const std::string &path, const std::vector<std::string> &tickers,
        const std::string &file_suffix, const bool &has_header_row)
        : path_(path), tickers_(tickers), file_suffix_(file_suffix), has_header_row_(has_header_row) {}

std::vector<DailyOhlcs> CsvReader::get_ohlc_data() const {
    std::string fname,
        line;
    std::ifstream fin;
    std::unordered_map<std::string, TickerOhlcMap> date_to_values;
    std::vector<DailyOhlcs> result;
    for (auto &ticker : tickers_) {
        fname = path_ + ticker + file_suffix_;
        fin.open(fname);
        if (!fin) {
            throw std::logic_error("could not open file " + fname);
        }
        // throw away header as needed
        if (has_header_row_) std::getline(fin, line);
        while (std::getline(fin, line)) {
            process_ohlc_line(date_to_values, ticker, line);
        }
        fin.close();
    }
    result.reserve(date_to_values.size());
    for (auto it = date_to_values.begin(); it != date_to_values.end(); ++it) {
        result.push_back({it->first, it->second});
    }
    std::sort(result.begin(), result.end(), [](DailyOhlcs x1, DailyOhlcs x2) 
            { return x1.date < x2.date; }); 
    return result;
}

std::vector<DailyRecommendations> CsvReader::get_recommendations() const {
    std::string fname,
        line;
    std::ifstream fin;
    std::unordered_map<std::string, std::unordered_map<std::string, double> > date_to_values;
    std::vector<DailyRecommendations> result;
    for (auto &ticker : tickers_) {
        fname = path_ + ticker + file_suffix_;
        fin.open(fname);
        if (!fin) {
            throw std::logic_error("could not open file " + fname);
        }
        // throw away header as needed
        if (has_header_row_) std::getline(fin, line);
        while (std::getline(fin, line)) {
            process_rec_line(date_to_values, ticker, line);
        }
        fin.close();
    }
    result.reserve(date_to_values.size());
    for (auto it = date_to_values.begin(); it != date_to_values.end(); ++it) {
        result.push_back({it->first, it->second});
    }
    std::sort(result.begin(), result.end(), [](DailyRecommendations x1, DailyRecommendations x2) 
            { return x1.date < x2.date; }); 
    return result;
}

void CsvReader::process_ohlc_line(std::unordered_map<std::string, TickerOhlcMap> &date_to_values, 
        const std::string &ticker, const std::string &line) {
    std::istringstream iss(line);
    std::string date,
        tmp;
    double open,
        high,
        low,
        close;

    std::getline(iss, date, ',');
    std::getline(iss, tmp, ',');
    open = std::stod(tmp);
    std::getline(iss, tmp, ',');
    high = std::stod(tmp);
    std::getline(iss, tmp, ',');
    low = std::stod(tmp);
    std::getline(iss, tmp, ',');
    close = std::stod(tmp);
    date_to_values[date][ticker] = { open, high, low, close };
}

void CsvReader::process_rec_line(std::unordered_map<std::string, 
        std::unordered_map<std::string, double> > &date_to_values, const std::string &ticker, 
        const std::string &line) {
    std::istringstream iss(line);
    std::string date,
        tmp;
    double strength;

    std::getline(iss, date, ',');
    std::getline(iss, tmp, ',');
    strength = std::stod(tmp);
    date_to_values[date][ticker] = strength;
}
