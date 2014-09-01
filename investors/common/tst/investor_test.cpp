/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor_test.cpp
 *
 * tests for abstract Investor class
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#include <iostream>
#include <string>
#include "investor.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

constexpr double EPSILON = 0.001;

bool approx(const double &, const double &);
// return false if a test has failed
bool show_msg(const char *, const bool &, int &, int &);

// concrete subclass for testing
class MyInvestor : public Investor {
    Order order(const std::string &ticker, const double &strength,
            const std::unordered_map<std::string, double> &price_list) const {
        Order order(Order::Type::kBuy, Order::Mode::kLimit, ticker, 0, 0.0);
        return order;
    }
};

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

    MyInvestor investor;

    // Initialization
    show_msg("watch list initially empty", investor.n_watched() == 0, passed, failed);
    show_msg("ticker1 not initially watched", !investor.watches(ticker1), passed, failed);
    show_msg("portfolio has no initial long positions", investor.portfolio()->n_long_pos() == 0, passed, failed);
    show_msg("portfolio has no initial cash", approx(investor.portfolio()->view_cash(), cash), passed, failed);

    // watch list
    investor.watch(ticker1).watch(ticker2);
    show_msg("watch list: 2 tickers added", investor.n_watched() == 2, passed, failed);
    show_msg("investor watches ticker2", investor.watches(ticker2), passed, failed);
    investor.unwatch(ticker2);
    show_msg("ticker2 removed from watch list", !investor.watches(ticker2), passed, failed);
    show_msg("watch list: 2 tickers added then 1 removed", investor.n_watched() == 1, passed, failed);

    // portfolio
    investor.portfolio()->deposit(deposit_amt);
    cash += deposit_amt;
    show_msg("deposit to portfolio successful", approx(investor.portfolio()->view_cash(), cash), passed, failed);
    investor.portfolio()->buy(ticker1, shares_bought, purchase_price);
    cash -= purchase_price;
    show_msg("correct cash after purchase", approx(investor.portfolio()->view_cash(), cash), passed, failed);
    show_msg("correct long position count after purchase", investor.portfolio()->n_long_pos() == 1, passed, failed);
    show_msg("correct shares after purchase", investor.portfolio()->shares(ticker1) == shares_bought, passed, failed);
    investor.portfolio()->sell(ticker1, shares_sold, sale_price);
    cash += sale_price;
    show_msg("correct cash after sale", approx(investor.portfolio()->view_cash(), cash), passed, failed);
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
