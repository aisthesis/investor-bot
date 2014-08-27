/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * portfolio_test.cpp
 *
 * tests for Portfolio class
 *
 * Author Marshall Farrier
 * Since 2014-08-25
 */

#include <iostream>
#include <string>
#include "portfolio.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

constexpr double EPSILON = 0.001;

bool approx(const double &, const double &);
// test assumes no stocks are owned initially
void test(Portfolio *cashonly_portfolio, double cash);
// return false if a test has failed
bool show_msg(const char *, const bool &, int &, int &);

int main() {
    std::cout << "Running tests on portfolio initialized with default constructor:" << std::endl;
    Portfolio pf1;
    test(&pf1, 0.0);
    constexpr double cash = 1000.0;
    Portfolio pf2(cash);
    std::cout << "Running tests on portfolio initialized with double:" << std::endl;
    test(&pf2, cash);
    return 0;
}

bool approx(const double &x1, const double &x2) {
    if (x1 >= x2) return x1 - x2 < EPSILON;
    return x2 - x1 < EPSILON;
}

void test(Portfolio *pf, double cash) {
    int passed = 0,
        failed = 0,
        shares1 = 0,
        shares2 = 0,
        shares3 = 0;
    double actual_cash = pf->view_cash();
    std::string eq1 = "foo",
        eq2 = "bar",
        eq3 = "blah";

    std::cout << "Testing initial cash." << std::endl;
    show_msg("initial cash", approx(actual_cash, cash), passed, failed);

    std::cout << "Testing initial stock ownership." << std::endl;
    show_msg("initial stock ownership", pf->shares(eq1) == shares1, passed, failed);

    std::cout << "Testing initial long positions." << std::endl;
    show_msg("initial long positions", pf->n_long_pos() == 0, passed, failed);
    
    std::cout << "Testing initial short positions." << std::endl;
    show_msg("initial short positions", pf->n_short_pos() == 0, passed, failed);

    std::cout << "Test buying shares." << std::endl;
    constexpr int shares_to_buy = 50;
    constexpr double cost = 200.0;
    pf->buy(eq1, shares_to_buy, cost);
    actual_cash -= cost;
    shares1 += shares_to_buy;
    // cash correct
    show_msg("cash after purchase", approx(pf->view_cash(), actual_cash), passed, failed);
    // shares correct
    show_msg("shares after purchase", shares1 == pf->shares(eq1), passed, failed);

    std::cout << "Test selling shares." << std::endl;
    constexpr int shares_to_sell = 23;
    constexpr double value = 193.1234890;
    pf->sell(eq1, shares_to_sell, value);
    pf->sell(eq2, shares_to_sell, value);
    pf->sell(eq3, shares_to_sell, value);
    actual_cash += 3.0 * value;
    shares1 -= shares_to_sell;  // 27
    shares2 -= shares_to_sell;  // -23
    shares3 -= shares_to_sell;
    // cash correct
    show_msg("cash after sales", approx(pf->view_cash(), actual_cash), passed, failed);
    // shares for eq1 correct
    show_msg("shares after buy and sell", shares1 == pf->shares(eq1), passed, failed);
    // shares for eq2 correct
    show_msg("shares after short sale", shares2 == pf->shares(eq2), passed, failed);
    // long position count correct
    show_msg("long position count after purchase and sale", pf->n_long_pos() == 1, passed, failed);
    // short position count correct
    show_msg("short position count after short sales", pf->n_short_pos() == 2, passed, failed);

    std::cout << passed << " tests passed." << std::endl
        << (failed > 0 ? BOLDRED : RESET) << failed << " tests failed." << RESET << std::endl << std::endl;
}

bool show_msg(const char *tst_desc, const bool &passing_condition, int &passed, int &failed) {
    if (passing_condition) {
        ++passed;
        return true;
    }
    ++failed;
    std::cout << BOLDRED << failed << " tests failed: " << tst_desc << RESET << std::endl << std::endl;
    return false;
}
