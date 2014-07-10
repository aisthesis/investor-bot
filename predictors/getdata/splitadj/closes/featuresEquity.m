## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{X} =} featuresEquity (@var{ticker}, @var{featureInterval})
## Generate and store the features for a given equity using saved list of split-adjusted
## closes.
##
## Example usage:
## X = featuresEquity("ge", 256);
## @end deftypefn

## Author: mdf
## Created: 2014-06-18

function [X] = featuresEquity(ticker, interval)

displayNow("featuresEquity() called");
INFILE_ROOT = getenv("DATA_ROOT");
INFILE_SUFFIX = "-splitadj.mat";
OUTFILE_ROOT = getenv("PREDICTOR_DATA_ROOT");
path = {"features" sprintf("%d", interval)};
pathTxt = createDir(path, OUTFILE_ROOT);
source('.octaverc');
OUTFILE_SUFFIX = ".mat";
outFile = sprintf("%s%s%s%s", OUTFILE_ROOT, pathTxt, ticker, OUTFILE_SUFFIX);

if exist(outFile)
    printfNow("Skipping file %s because it already exists.\nDelete file and rerun this function to rebuild it.\n\n", outFile);
    return;
endif

inFile = sprintf("%s%s%s", INFILE_ROOT, ticker, INFILE_SUFFIX);
load(inFile);
X = getFeatures(closes, interval);
currDate = sessionDates(interval:end, :);

save("-mat-binary", outFile, "X", "currDate");
printfNow("file %s created.\n", outFile);

endfunction
