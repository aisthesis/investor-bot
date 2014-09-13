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

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "simulator.h"
#include "csv_reader.h"
#include "finance.h"
#include "globals.h"
#include "investor01.h"
#include "order_action.h"

int main() {
    // investor will start with 1000.0 dollars
    Investor01 investor;
    investor.deposit(1000.0);
    // get input data
    const std::string kProjectRoot = "../../../";
    std::vector<std::string> tickers = { "cat", "dd", "f", "ge", "ibm", "jnj", "jpm", "xom" };
    // ohlc data
    std::string suffix = "-splitadj.csv";
    std::string path = kProjectRoot + "data/";
    CsvReader ohlc_reader(path, tickers, suffix);
    std::cout << "Reading ohlc data" << std::endl;
    std::vector<DailyOhlcs> ohlc_data = ohlc_reader.get_ohlc_data();
    std::cout << "Finished reading ohlc data" << std::endl;
    // recommendations
    path = kProjectRoot + "recommenders/00/output/";
    CsvReader rec_reader(path, tickers);
    std::cout << "Reading recommendations" << std::endl;
    std::vector<DailyRecommendations> recommendations = rec_reader.get_recommendations();
    std::cout << "Finished reading recommendations" << std::endl;
    // create simulator
    Simulator simulator(investor, ohlc_data, recommendations);
    // run simulation
    std::cout << "Running simulation" << std::endl;
    simulator.run();
    std::cout << "Getting simulation order actions" << std::endl;
    std::vector<OrderAction> actions = simulator.actions();
    std::cout << "Simulation complete" << std::endl;
    
    // report results
    std::cout << "Reporting results" << std::endl;
    std::ofstream ofs("../output/SIM00.md");
    ofs << "sim00" << std::endl << "===" << std::endl;
    ofs << "Description" << std::endl << "---" << std::endl;
    ofs << "Uses:" << std::endl;
    ofs << "- recommenders/00" << std::endl;
    ofs << "- investors/01" << std::endl;
    ofs << "Results" << std::endl << "---" << std::endl;
    ofs << "### Summary" << std::endl;
    ofs << "Bankroll on " << simulator.start_date() << " : " << std::fixed 
            << std::setprecision(2) << simulator.start_value() << std::endl;
    ofs << "Bankroll on " << simulator.end_date() << " : " << std::fixed 
            << std::setprecision(2) << simulator.end_value() << std::endl;
    ofs << "Average annual gain: " << std::setprecision(2) << simulator.end_value() 
            << Finance::annual_pct_return(simulator.start_date(), simulator.start_value(),
            simulator.end_date(), simulator.end_value()) << " pct" << std::endl;
    ofs << "### Actions" << std::endl;
    for (auto action : actions) {
        ofs << action << std::endl;
    }
    ofs.close();
    std::cout << "Done!" << std::endl;
    return 0;
}
