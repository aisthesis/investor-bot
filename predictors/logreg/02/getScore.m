## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} getScore ()
## Return and save @var{F1score}, @var{precision} and @var{recall}
## over the test dataset.
##
## Usage:
## 
## @example
## [score, precision, recall] = getScore()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-10

function [score, precision, recall] = getScore()
    
    % parameters used:
    featureInterval = 256;
    labelInterval = 64;
    labelType = "bullish";
    ratio = 1.0;
    ofname = "output/score.mat";
    PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");

    % load learned theta
    load("output/learned.mat");
    
    % load test data
    infile = sprintf("%s/train70test30/splitadj/closes/test/features/%d/labels/%d/%s/%dpct/combined.mat", ...
        PREDICTOR_DATA_ROOT, featureInterval, labelInterval, labelType, floor(ratio * 100));
    load(infile);

    % add constant feature
    m = size(X, 1);
    X = [ones(m, 1), X];

    % get predicted values
    predicted = lrPredict(X, theta);

    % get scores
    [score, precision, recall] = fscore(predicted, y);

    % save
    save("-mat-binary", ofname, "score", "precision", "recall");

endfunction
