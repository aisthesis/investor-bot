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
 *
 * Author Marshall Farrier
 * Since 2014-08-29
 */

#include <iostream>
#include <string>
#include "investor01.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

constexpr double EPSILON = 0.001;

bool approx(const double &, const double &);
// return false if a test has failed
bool show_msg(const char *, const bool &, int &, int &);

int main() {
    int passed = 0,
        failed = 0;
    std::string ticker1 = "blah",
        ticker2 = "foo";
    double deposit_amt = 1000.0,
        cash = 0.0;
    int shares_bought = 5,
        shares_sold = 3;
    int purchase_price = 100.0,
        sale_price = 200.0;

    Investor01 investor;

    std::cout << 1.0 / 3 << std::endl;
    std::cout << 1 / 3.0 << std::endl;
    // Initialization
    show_msg("portfolio has no initial long positions", investor.portfolio()->n_long_pos() == 0, passed, failed);
    show_msg("portfolio has no initial cash", approx(investor.portfolio()->cash(), cash), passed, failed);

    // portfolio
    investor.portfolio()->deposit(deposit_amt);
    cash += deposit_amt;
    show_msg("deposit to portfolio successful", approx(investor.portfolio()->cash(), cash), passed, failed);
    investor.portfolio()->buy(ticker1, shares_bought, purchase_price);
    cash -= purchase_price;
    show_msg("correct cash after purchase", approx(investor.portfolio()->cash(), cash), passed, failed);
    show_msg("correct long position count after purchase", investor.portfolio()->n_long_pos() == 1, passed, failed);
    show_msg("correct shares after purchase", investor.portfolio()->shares(ticker1) == shares_bought, passed, failed);
    investor.portfolio()->sell(ticker1, shares_sold, sale_price);
    cash += sale_price;
    show_msg("correct cash after sale", approx(investor.portfolio()->cash(), cash), passed, failed);
    show_msg("correct long position count after sale", investor.portfolio()->n_long_pos() == 1, passed, failed);

    std::cout << passed << " tests passed." << std::endl
        << (failed > 0 ? BOLDRED : RESET) << failed << " tests failed." << RESET << std::endl << std::endl;
    
    return 0;
}

bool approx(const double &x1, const double &x2) {
    if (x1 >= x2) return x1 - x2 < EPSILON;
    return x2 - x1 < EPSILON;
}

bool show_msg(const char *tst_desc, const bool &passing_condition, int &passed, int &failed) {
    if (passing_condition) {
        ++passed;
        return true;
    }
    ++failed;
    std::cout << BOLDRED << "test failed: " << tst_desc << RESET << std::endl << std::endl;
    return false;
}
