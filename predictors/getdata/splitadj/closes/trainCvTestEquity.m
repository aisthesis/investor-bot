## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} trainCvTestEquity (@var{ticker}, @var{featureInterval},
## @var{labelInterval}, @var{bullMinRatio}, @var{upsideMinRatio}, @var{bearMaxRatio})
## Generate and store training, cross-validation and test datasets for the given
## equity.
## 
## The ratio training-cv-test will be 60-20-20, and the chronological
## order of the chosen set will be determined by a randomly generated permutation
## of [1:3] stored in `eqDataDivisions.mat`. If the permuation associated with
## ticker "dd" is, for example, [3 1 2], then the first 20pct of data will be used
## for testing (3), the middle 60pct for training (1), and the last 20pct for cross-
## validation (2).
##
## Example usage:
##
## @example
## trainCvTestEquity("cat", 256, 64, 4.0, 1.25, 1.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-06-18

function trainCvTestEquity(labelType, ticker, featureInterval, labelInterval, ratio);

displayNow("trainCvTestEquity() called");

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
SIZES = [0.6 0.2 0.2];
NAMES = {"train" "xval" "test"};
N_NAMES = length(NAMES);
path = cell(1, 1);
nRows = 0;
nRelevantFeatureRows = 0;
startRow = 1;
ofile = "";

% get permutation for equity
permutationsFile = sprintf("%s%s", PREDICTOR_DATA_ROOT, "eqDataDivisions.mat");
load(permutationsFile);
permutation = permutations.(ticker);

% create directories
for i = 1:N_NAMES
    path = {NAMES{i} "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
        labelType sprintf("%dpct", floor(ratio * 100))};
    createDir(path, PREDICTOR_DATA_ROOT);
endfor

% load features
load(sprintf("%sfeatures/%d/%s.mat", PREDICTOR_DATA_ROOT, featureInterval, ticker));
Xall = X;
dateXall = currDate;
nRelevantFeatureRows = size(Xall, 1) - 2 * featureInterval + 2 - labelInterval;

% load labels
load(sprintf("%slabels/%d/%s/%dpct/%s.mat", PREDICTOR_DATA_ROOT, labelInterval, labelType, ...
    floor(ratio * 100), ticker));
yAll = y;

% separate and save data sets
for i = 1:N_NAMES
    ofile = sprintf("%s%s/features/%d/labels/%d/%s/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, labelType, floor(ratio * 100), ticker);

    if exist(ofile)
        printfNow("Skipping file %s because it already exists.\nDelete file and rerun this function to rebuild it.\n\n", ofile);
        continue;
    endif

    nRows = floor(SIZES(i) * nRelevantFeatureRows);
    X = Xall(startRow : startRow + nRows - 1, :);
    currDate = dateXall(startRow : startRow + nRows - 1, :);
    y = yAll(startRow + featureInterval - 1 : startRow + featureInterval + nRows - 2, :);
    printfNow(". ");
    save("-mat-binary", ofile, "X", "y", "currDate");
    printfNow(". ");
endfor
displayNow("");

endfunction
