## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} getRecommendations ()
## Save recommendations for target equities in matlab binary form.
##
## Use the equities and time periods from predictors/01 but
## always outputs 1 (buy) as baseline.
##
## Usage:
## 
## @example
## getRecommendations()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-15

function getRecommendations()
    OUTFILE_PATH = "output";
    OUTFILE_SUFFIX = "mat";
    PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
    PREDICTOR_ALGORITHM_ROOT = getenv("PREDICTOR_ALGORITHM_ROOT");

    infile = "equities.csv";
    ofile = "";
    strength = [];

    % get equities to be used
    equities = textread(sprintf("%s%s", PREDICTOR_DATA_ROOT, infile), "%s");
    nEq = size(equities, 1);

    % get predictions for each equity and save
    for i = 1:nEq
        printfNow("Loading predictions for equity '%s'.\n", equities{i});
        % load prediction file for equity
        load(sprintf("%s01/output/%s.mat", PREDICTOR_ALGORITHM_ROOT, equities{i}));
        % set strengths
        displayNow("Generating strengths.");
        strength = label;
        % save results
        displayNow("Saving strengths.");
        ofile = sprintf("%s/%s.%s", OUTFILE_PATH, equities{i}, OUTFILE_SUFFIX);
        save("-mat-binary", ofile, "currDate", "strength");
    endfor
endfunction
