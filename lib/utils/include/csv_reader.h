/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * csv_reader.h
 *
 * Reads csv files and generates output in desired data format.
 * Throw logic_error exception if data in file cannot be translated
 * into the desired output format.
 *
 * Author Marshall Farrier
 * Since 2014-09-10
 */

#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>

#include "globals.h"

class CsvReader {
private:
    const std::string path_;
    const std::vector<std::string> tickers_;
    const std::string file_suffix_;
    const bool has_header_row_;
public:
    CsvReader(const std::string &path, const std::vector<std::string> &tickers, 
            const std::string &file_suffix = ".csv", const bool &has_header_row = true);
    ~CsvReader() {}

    std::vector<DailyOhlcs> get_ohlc_data() const;
    std::vector<DailyRecommendations> get_recommendations() const;
private:
    static void process_ohlc_line(std::unordered_map<std::string, TickerOhlcMap> &date_to_values, 
            const std::string &ticker, const std::string &line); 
    static void process_rec_line(std::unordered_map<std::string, 
            std::unordered_map<std::string, double> > &date_to_values, const std::string &ticker, 
            const std::string &line);
};
#endif
