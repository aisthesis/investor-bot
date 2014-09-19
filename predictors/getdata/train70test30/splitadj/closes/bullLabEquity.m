## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{ret}=} bullLabEquity (@var{ticker}, @var{interval}, @var{minRatio})
## Given a ticker, an interval, and a maximum ratio, return and save
## labels for all available data for the given equity.
##
## If the given labels have already been saved, the function returns 1 for
## @var{alreadyExists} and otherwise does nothing.
##
## Usage:
##
## @example
## [y, alreadyExists] = bullLabEquity("ge", 256, 1.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-18

function [y, alreadyExists] = bullLabEquity(ticker, interval, minRatio)

DATA_ROOT = getenv("DATA_ROOT");
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/train70test30/splitadj/closes", PREDICTOR_DATA_ROOT);

y = [];
alreadyExists = 0;
path = {"labels" sprintf("%d", interval) "bullish" sprintf("%dpct", floor(minRatio * 100))};
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
y = getBullishLabels(closes, interval, minRatio);
currDate = sessionDates(1:end - interval);
save("-mat-binary", outFile, "y", "currDate");
printfNow("file %s created.\n", outFile);

end
