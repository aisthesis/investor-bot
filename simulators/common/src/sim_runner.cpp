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
#include <locale>
#include <string>
#include <vector>

#include "comma_numpunct.h"
#include "csv_reader.h"
#include "finance.h"
#include "globals.h"
#include "order_action.h"
#include "sim_runner.h"
#include "simulator.h"

SimRunner::SimRunner(Investor &investor, const std::string &inv_label, const std::string &recommender_label,
        const std::vector<std::string> &tickers, const std::string &path_to_project_root,
        const double &start_bankroll, const std::string &ohlc_file_suffix) 
    : inv_label_(inv_label), recommender_label_(recommender_label), tickers_(tickers), 
            ohlc_file_suffix_(ohlc_file_suffix), path_to_project_root_(path_to_project_root) {
    investor_ = &investor;
    investor_->deposit(start_bankroll);
}

SimRunner::~SimRunner() {
    delete simulator_;
}

void SimRunner::run() {
    get_ohlc_data();
    get_recommendations();
    run_simulation();
    report_results();
    std::cout << "Done!" << std::endl;
}

void SimRunner::get_ohlc_data() {
    std::string path = path_to_project_root_ + "data/";
    std::cout << "Reading ohlc data" << std::endl;
    ohlc_data_ = CsvReader(path, tickers_, ohlc_file_suffix_).get_ohlc_data();
    std::cout << "Finished reading ohlc data" << std::endl;
}

void SimRunner::get_recommendations() {
    std::string path = path_to_project_root_ + "recommenders/" + recommender_label_ + "/output/";
    std::cout << "Reading recommendations" << std::endl;
    recommendations_ = CsvReader(path, tickers_).get_recommendations();
    std::cout << "Finished reading recommendations" << std::endl;
}

void SimRunner::run_simulation() {
    simulator_ = new Simulator(*investor_, ohlc_data_, recommendations_);
    std::cout << "Running simulation" << std::endl;
    simulator_->run();
    std::cout << "Getting simulation order actions" << std::endl;
    actions_ = simulator_->actions();
    std::cout << "Simulation complete" << std::endl;
}

void SimRunner::report_results() {
    constexpr int kValueWidth = 13;
    std::locale comma_locale(std::locale(), new comma_numpunct());

    std::cout << "Reporting results" << std::endl;
    std::ofstream ofs("../output/SIM_RESULTS.md");
    ofs.imbue(comma_locale);
    ofs << std::fixed << std::setprecision(2) << std::right;
    ofs << "Simulation Summary" << std::endl << "===" << std::endl;
    ofs << "Description" << std::endl << "---" << std::endl;
    ofs << "Uses:" << std::endl;
    ofs << "- recommenders/" + recommender_label_ << std::endl;
    ofs << "- investors/" + inv_label_ << std::endl << std::endl;
    ofs << "Results" << std::endl << "---" << std::endl;
    ofs << "### Summary" << std::endl;
    ofs << "    Bankroll on " << simulator_->start_date() << " : $" << std::setw(kValueWidth) 
            << simulator_->start_value() << std::endl << std::endl;
    ofs << "    Bankroll on " << simulator_->end_date() << " : $" << std::setw(kValueWidth)
            << simulator_->end_value() << std::endl << std::endl;
    ofs << "    Average annual gain : "
            << Finance::annual_pct_return(simulator_->start_date(), simulator_->start_value(),
            simulator_->end_date(), simulator_->end_value()) << " pct" << std::endl << std::endl;
    ofs << "### Actions" << std::endl;
    for (auto action : actions_) {
        ofs << "- " << action << std::endl;
    }
    ofs.close();
}
