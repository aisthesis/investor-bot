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
#include <vector>

#include "investor.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

constexpr double EPSILON = 0.001;

bool approx(const double &, const double &);
// return false if a test has failed
bool show_msg(const char *, const bool &, int &, int &);

// concrete subclass for testing
class MyInvestor : public Investor {
    std::vector<Order> order(const std::unordered_map<std::string, double> &strengths,
            const std::unordered_map<std::string, double> &price_list) {
        return std::vector<Order>();
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
    double purchase_price = 100.0,
        sale_price = 200.0,
        add_to_pending = 3.14;

    MyInvestor investor;

    // Initialization
    show_msg("portfolio has no initial long positions", investor.n_long_pos() == 0, passed, failed);
    show_msg("portfolio has no initial cash", approx(investor.cash(), cash), passed, failed);
    show_msg("no initial pending purchases", approx(investor.pending(), 0.0), passed, failed);

    // pending purchases
    double pending = investor.add_to_pending(add_to_pending);
    show_msg("correct amount added to pending", approx(investor.pending(), add_to_pending), passed, failed);
    show_msg("correct amount returned when adding to pending", approx(pending, add_to_pending), passed, failed);
    investor.clear_pending();
    show_msg("pending correctly cleared", approx(investor.pending(), 0.0), passed, failed);

    // portfolio
    investor.deposit(deposit_amt);
    cash += deposit_amt;
    show_msg("deposit to portfolio successful", approx(investor.cash(), cash), passed, failed);
    investor.buy(ticker1, shares_bought, purchase_price);
    cash -= purchase_price;
    show_msg("correct cash after purchase", approx(investor.cash(), cash), passed, failed);
    show_msg("correct long position count after purchase", investor.n_long_pos() == 1, passed, failed);
    show_msg("correct shares after purchase", investor.shares(ticker1) == shares_bought, passed, failed);
    investor.sell(ticker1, shares_sold, sale_price);
    cash += sale_price;
    show_msg("correct cash after sale", approx(investor.cash(), cash), passed, failed);
    show_msg("correct long position count after sale", investor.n_long_pos() == 1, passed, failed);
    int counter = 0,
        tmp_shares = 0;
    std::string tmp_ticker = "";
    for (auto it = investor.pfbegin(); it != investor.pfend(); it++) {
        counter++;
        tmp_ticker = it->first;
        tmp_shares = it->second;
    }
    show_msg("correct number of iterations", counter  == 1, passed, failed);
    show_msg("iterator picks up correct ticker", tmp_ticker == ticker1, passed, failed);
    show_msg("iterator picks up correct shares", tmp_shares == shares_bought - shares_sold, passed, failed);

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
