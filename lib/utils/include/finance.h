/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * finance.h
 *
 * non-instantiable class with static methods for financial calculations
 *
 * Author Marshall Farrier
 * Since 2014-09-12
 */

#ifndef FINANCE_H
#define FINANCE_H

#include <string>

class Finance {
private:
    Finance() {}
public:
    static int year(const std::string &yyyy_mm_dd);
    static int month(const std::string &yyyy_mm_dd);
    static int day_of_month(const std::string &yyyy_mm_dd);
    static int date_diff(const std::string &earlier, const std::string &later);
};
#endif
