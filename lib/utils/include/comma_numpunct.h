/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * comma_numpunct.h
 *
 * Class for number formatting using thousand separators
 * http://stackoverflow.com/questions/7276826/c-format-number-with-commas
 *
 * Author Marshall Farrier
 * Since 2014-09-14
 */

#ifndef COMMA_NUMPUNCT_H
#define COMMA_NUMPUNCT_H

#include <locale>
#include <string>

class comma_numpunct : public std::numpunct<char> {
protected:
    virtual char do_thousands_sep() const { return ','; }
    virtual std::string do_grouping() const { return "\03"; }
};
#endif
