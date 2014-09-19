## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{ret} =} featuresEquity (@var{ticker}, @var{featureInterval})
## Generate and store the features for a given equity using saved list of split-adjusted
## closes.
##
## If the given features have already been saved, the function returns 1 for
## @var{alreadyExists} and otherwise does nothing.
##
## Example usage:
## [X, alreadyExists] = featuresEquity("ge", 256);
## @end deftypefn

## Author: mdf
## Created: 2014-09-18

function [X, alreadyExists] = featuresEquity(ticker, interval)

DATA_ROOT = getenv("DATA_ROOT");
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/splitadj/closes", PREDICTOR_DATA_ROOT);

X = [];
alreadyExists = 0;
path = {"features" sprintf("%d", interval)};
pathTxt = createDir(path, algoDataRoot);
source('.octaverc');
outFile = sprintf("%s/%s%s.mat", algoDataRoot, pathTxt, ticker);

% just return if file already exists
if exist(outFile, "file")
    alreadyExists = 1;
    return;
endif

inFile = sprintf("%s/%s-splitadj.mat", DATA_ROOT, ticker);
load(inFile);
X = getFeatures(closes, interval);
currDate = sessionDates(interval:end, :);
save("-mat-binary", outFile, "X", "currDate");
printfNow("file %s created.\n", outFile);

endfunction
