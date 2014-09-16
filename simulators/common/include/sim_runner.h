/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * sim_runner.h
 *
 * SimRunner class
 * Wrapper for Simulator class to take minimum required input to
 * run simulation and write the results.
 *
 * Author Marshall Farrier
 * Since 2014-09-14
 */

#ifndef SIM_RUNNER_H
#define SIM_RUNNER_H

#include <string>
#include <vector>

#include "globals.h"
#include "investor.h"
#include "order_action.h"
#include "simulator.h"

class SimRunner {
private:
    Investor *investor_;
    const std::string inv_label_;
    const std::string recommender_label_;
    const std::vector<std::string> tickers_;
    const std::string ohlc_file_suffix_;
    const std::string path_to_project_root_;

    // populated on run:
    std::vector<DailyOhlcs> ohlc_data_;
    std::vector<DailyRecommendations> recommendations_;
    std::vector<OrderAction> actions_;
    Simulator *simulator_;
public:
    // recommender_label MUST correspond to a subdirectory of ./recommenders, e.g. "01", etc.
    // it is used not only for printed output but also for finding the recommendation file
    SimRunner(Investor &investor, const std::string &inv_label, const std::string &recommender_label,
            const std::vector<std::string> &tickers, const std::string &path_to_project_root = "../../../", 
            const double &start_bankroll = 10000.0, const std::string &ohlc_file_suffix = "-splitadj.csv");
    ~SimRunner();

    void run();
private:
    void get_ohlc_data();
    void get_recommendations();
    void run_simulation();
    void report_results() const;
    std::vector<std::pair<std::string, int> > get_positions() const;
};
#endif
