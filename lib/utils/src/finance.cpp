/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * finance.cpp
 *
 * non-instantiable class with static methods for financial calculations
 *
 * Author Marshall Farrier
 * Since 2014-09-12
 */

#include <string>
#include <cmath>

#include "finance.h"

int Finance::year(const std::string &yyyy_mm_dd) {
    return std::stoi(yyyy_mm_dd.substr(0, 4));
}

int Finance::month(const std::string &yyyy_mm_dd) {
    return std::stoi(yyyy_mm_dd.substr(5, 2));
}

int Finance::day_of_month(const std::string &yyyy_mm_dd) {
    return std::stoi(yyyy_mm_dd.substr(8, 2));
}

int Finance::date_diff(const std::string &earlier, const std::string &later) {
    // Note that December is irrelevant for cumulative days
    // months:                                  31, 28, 31,  30,  31,  30,  31,  31,  30,  31,  30, 31 
    static const int month_cumulative_days[] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}; 
    int yr1 = year(earlier),
        yr2 = year(later),
        mo1 = month(earlier),
        mo2 = month(later),
        result = 365 * (yr2 - yr1);

    if (mo1 > 1) {
        result -= month_cumulative_days[mo1 - 2];
    }
    if (mo2 > 1) {
        result += month_cumulative_days[mo2 - 2];
    }
    result += day_of_month(later) - day_of_month(earlier);

    // leap years (valid 1901-2099)
    result += (yr2 - yr1) / 4;
    if (yr1 % 4 == 0 && mo1 <= 2) ++result;
    if (yr2 % 4 == 0 && mo2 <= 2) --result;
    return result;
}

double Finance::annual_mult(const std::string &start_date, const double &start_value,
        const std::string &end_date, const double &end_value) {
    int days = date_diff(start_date, end_date);
    double yrs = days / 365.25, 
        mult = end_value / start_value,
        ln_mult = std::log(mult);

    return std::exp(ln_mult / yrs);
}

double Finance::annual_pct_return(const std::string &start_date, const double &start_value,
        const std::string &end_date, const double &end_value) {
    return (annual_mult(start_date, start_value, end_date, end_value) - 1.0) * 100.0;
}
