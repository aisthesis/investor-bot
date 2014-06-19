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
## trainCvTestEquity("cat", 256, 64, 4.0, 1.25, 1.0);
## @end deftypefn

## Author: mdf
## Created: 2014-06-18

function trainCvTestEquity(ticker, featureInterval, labelInterval, bullMinRatio, upsideMinRatio, bearMaxRatio);

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
SIZES = [0.6 0.2 0.2];
NAMES = {"train" "xval" "test"};
N_NAMES = length(NAMES);
path = cell(1, 1);
nRows = 0;
nRelevantFeatureRows = 0;
startRow = 1;

% get permutation for equity
permutationsFile = sprintf("%s%s", PREDICTOR_DATA_ROOT, "eqDataDivisions.mat");
load(permutationsFile);
permutation = getPermutation(ticker, permutations);

% create directories
for i = 1:N_NAMES
    path = {NAMES{i} "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
        "bullish" sprintf("%dpct", floor(bullMinRatio * 100))};
    createDir(path, PREDICTOR_DATA_ROOT);
    path = {NAMES{i} "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
        "bearish" sprintf("%dpct", floor(bearMaxRatio * 100))};
    createDir(path, PREDICTOR_DATA_ROOT);
    path = {NAMES{i} "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
        "upside-exceeded" sprintf("%dpct", floor((upsideMinRatio - 1) * 100))};
    createDir(path, PREDICTOR_DATA_ROOT);
endfor

% load features
load(sprintf("%sfeatures/%d/%s.mat", PREDICTOR_DATA_ROOT, featureInterval, ticker));
Xall = X;
dateXall = currDate;
nRelevantFeatureRows = size(Xall, 1) - 2 * featureInterval + 2 - labelInterval;

% load labels
load(sprintf("%slabels/%d/bullish/%dpct/%s.mat", PREDICTOR_DATA_ROOT, labelInterval, ...
    floor(bullMinRatio * 100), ticker));
bullLabAll = y;
load(sprintf("%slabels/%d/bearish/%dpct/%s.mat", PREDICTOR_DATA_ROOT, labelInterval, ...
    floor(bearMaxRatio * 100), ticker));
bearLabAll = y;
load(sprintf("%slabels/%d/upside-exceeded/%dpct/%s.mat", PREDICTOR_DATA_ROOT, labelInterval, ...
    floor((upsideMinRatio - 1) * 100), ticker));
upsExLabAll = y;

% separate and save data sets
for i = 1:N_NAMES
    nRows = floor(SIZES(i) * nRelevantFeatureRows);
    X = Xall(startRow : startRow + nRows - 1, :);
    currDate = dateXall(startRow : startRow + nRows - 1, :);
    y = bullLabAll(startRow + featureInterval - 1 : startRow + featureInterval + nRows - 2, :);
    printfNow(". ");
    save("-mat-binary", sprintf("%s%s/features/%d/labels/%d/bullish/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, floor(bullMinRatio * 100), ticker), "X", "y", "currDate");
    y = bearLabAll(startRow + featureInterval - 1 : startRow + featureInterval + nRows - 2, :);
    printfNow(". ");
    save("-mat-binary", sprintf("%s%s/features/%d/labels/%d/bearish/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, floor(bearMaxRatio * 100), ticker), "X", "y", "currDate");
    y = upsExLabAll(startRow + featureInterval - 1 : startRow + featureInterval + nRows - 2, :);
    printfNow(". ");
    save("-mat-binary", sprintf("%s%s/features/%d/labels/%d/upside-exceeded/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, floor((upsideMinRatio - 1) * 100), ticker), "X", "y", "currDate");
    startRow = startRow + nRows + featureInterval - 1;
    printfNow(". ");
endfor
displayNow("");

end
