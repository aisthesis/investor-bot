## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} savePredictions (@var{equityFeaturePath}, @var{equitiesFile})
## Save predictions for target equities in matlab binary form.
##
## Uses the value of @var{theta} that is assumed to have been saved
## with a call to @code{learn()}
##
## Dependencies:
##
## @itemize
## @item
## @code{learn()} must be run prior to running this script.
## @end itemize
##
## Usage:
## 
## @example
## savePredictions("splitadj/closes/features/256/mean0/std100pct", "splitadj/closes/equities.csv")
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-21

function savePredictions(equityFeaturePath, equitiesFile)
    
    PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");

    infile = sprintf("%s/equities.csv", PREDICTOR_DATA_ROOT);
    ofile = "";
    m = 0;

    % get equities to be used
    equities = textread(sprintf("%s/%s", PREDICTOR_DATA_ROOT, equitiesFile), "%s");
    nEq = size(equities, 1);

    displayNow("ok to here");
    return;

    % get parameters
    load("params.mat");

    % get theta
    load("output/learned.mat");

    % run predictor on each equity and save results
    for i = 1:nEq
        printfNow("Retrieving labels for equity '%s'.\n", equities{i});
        % load equity features
        load(sprintf("%sfeatures/%d/%s.mat", PREDICTOR_DATA_ROOT, featureInterval, equities{i}));
        % append constant feature
        m = size(X, 1);
        X = [ones(m, 1), X];
        % get predictions
        label = lrPredict(X, theta);
        % save results
        printfNow("Saving labels for equity '%s'.\n", equities{i});
        ofile = sprintf("%s/%s.%s", OUTFILE_PATH, equities{i}, OUTFILE_SUFFIX);
        save("-mat-binary", ofile, "currDate", "label");

    endfor

endfunction
