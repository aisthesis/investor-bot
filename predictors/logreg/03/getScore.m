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
## In addition, score, precision and recall are returned for a baseline
## predictor which is simply a vector of all 1s.
##
## Usage:
## 
## @example
## [score, precision, recall, blScore, blPrecision, blRecall] = getScore()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-10

function [score, precision, recall, blScore, blPrecision, blRecall] = getScore()
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters used:
featureInterval = 256;
labelInterval = 64;
labelType = "bullish";
ratio = 1.0;
dataRootPath = "splitadj/closes/train60xval20test20";
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ofname = "output/score.mat";
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");

% load learned theta
load("output/learned.mat");

% load test data
infile = sprintf("%s/%s/test/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, dataRootPath, featureInterval, labelInterval, labelType, floor(ratio * 100));
load(infile);

% add constant feature
m = size(X, 1);
X = [ones(m, 1), X];

% get predicted values
predicted = lrPredict(X, theta);
baseline = ones(m, 1);

% get scores
[score, precision, recall] = fscore(predicted, y);
[blScore, blPrecision, blRecall] = fscore(baseline, y);

% save
save("-mat-binary", ofname, "score", "precision", "recall", "blScore", "blPrecision", "blRecall");

endfunction
