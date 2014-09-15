/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * sim00.cpp
 *
 * Executable to run baseline simulation.
 * Uses:
 * recommenders/00
 * investors/01
 *
 * Author Marshall Farrier
 * Since 2014-09-12
 */

#include <string>
#include <vector>

#include "sim_runner.h"
#include "investor01.h"

int main() {
    Investor01 investor;
    std::string inv_label = "01";
    std::string recommender_label = "00";
    std::vector<std::string> tickers = { "cat", "dd", "f", "ge", "ibm", "jnj", "jpm", "xom" };

    SimRunner(investor, inv_label, recommender_label, tickers).run();
    return 0;
}
