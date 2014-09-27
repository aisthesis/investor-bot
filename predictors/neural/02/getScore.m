## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{score} =} getScore (@var{weightId})
## Return and save @var{F1score}, @var{precision} and @var{recall}
## over the test and training datasets.
##
## In addition, score, precision and recall are returned for a baseline
## predictor which is simply a vector of all 1s.
##
## Usage:
## 
## @example
## score  = getScore("01")
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-27

function score = getScore(weightId)
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters used:
featureInterval = 256;
labelInterval = 64;
labelType = "bullish";
ratio = 1.0;
dataRootPath = "splitadj/closes/train60xval20test20";
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ofname = sprintf("output/score%s.mat", weightId);
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
score = {};
score.testLearned = {};
score.trainLearned = {};
score.testBaseline = {};
score.trainBaseline = {};

% load learned theta
infile = sprintf("output/learned%s.mat", weightId);
load(infile);

% load test data
infile = sprintf("%s/%s/test/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, dataRootPath, featureInterval, labelInterval, labelType, floor(ratio * 100));
load(infile);

m = size(X, 1);

% get predicted values
h1 = sigmoid([ones(m, 1) X] * theta1');
h2 = sigmoid([ones(m, 1) h1] * theta2');
predicted = h2 >= 0.5;

% get scores for test set and test baseline
[score.testLearned.f1, score.testLearned.precision, score.testLearned.recall] = fscore(predicted, y);
baseline = ones(m, 1);
[score.testBaseline.f1, score.testBaseline.precision, score.testBaseline.recall] = fscore(baseline, y);

% load training data
infile = sprintf("%s/%s/train/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, dataRootPath, featureInterval, labelInterval, labelType, floor(ratio * 100));
load(infile);

m = size(X, 1);

% get predicted values
h1 = sigmoid([ones(m, 1) X] * theta1');
h2 = sigmoid([ones(m, 1) h1] * theta2');
predicted = h2 >= 0.5;

% get scores for training set
[score.trainLearned.f1, score.trainLearned.precision, score.trainLearned.recall] = fscore(predicted, y);
baseline = ones(m, 1);
[score.trainBaseline.f1, score.trainBaseline.precision, score.trainBaseline.recall] = fscore(baseline, y);

% save
save("-mat-binary", ofname, "score");

endfunction
