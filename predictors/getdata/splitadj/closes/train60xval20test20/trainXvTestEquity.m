## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{alreadyExists}=} trainXvTestEquity (@var{labelType}, @var{ticker}, @var{featureInterval},
## @var{labelInterval}, @var{ratio})
## Generate and store training and test datasets for the given
## equity and label type.
## 
## The ratio training-test will be 70-30, and the chronological
## order of the chosen set will be determined by a randomly generated permutation
## of [1:2] stored in `eqDataDivisions.mat`. If the permuation associated with
## ticker "dd" is, for example, [2 1], then the first 30pct of data will be used
## for testing (2) and the last 70pct for training (1).
##
## If both training and test data already exist, the function returns 1 and
## otherwise does nothing.
##
## Example usage:
##
## @example
## alreadyExists = trainXvTestEquity("bullish", "cat", 256, 64, 4.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function alreadyExists = trainXvTestEquity(labelType, ticker, featureInterval, labelInterval, ratio);

alreadyExists = 1;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/splitadj/closes", PREDICTOR_DATA_ROOT);
sepNames = {"train" "xval" "test"};
nSepNames = length(sepNames);
path = {};
sepPaths = {};
sepFiles = {};
for i = 1:nSepNames
    path = {"train60xval20test20" sepNames{i} "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
        labelType sprintf("%dpct", floor(ratio * 100))};
    sepPaths{i} = createDir(path, algoDataRoot);
    sepFiles{i} = sprintf("%s/%s%s.mat", algoDataRoot, sepPaths{i}, ticker);
    alreadyExists = alreadyExists && exist(sepFiles{i}, "file");
endfor

if alreadyExists
    return;
endif

sizes = [0.6 0.2 0.2];
% get permutation for equity
permutationsFile = sprintf("%s/divisions-3.mat", algoDataRoot);
load(permutationsFile);
permutation = permutations.(ticker);

% load features
load(sprintf("%s/features/%d/%s.mat", algoDataRoot, featureInterval, ticker));
Xall = X;
dateXall = currDate;
nRelevantFeatureRows = size(Xall, 1) - 2 * (featureInterval - 1) - labelInterval;

% load labels
load(sprintf("%s/labels/%d/%s/%dpct/%s.mat", algoDataRoot, labelInterval, labelType, ...
    floor(ratio * 100), ticker));
yAll = y;

% separate and save data sets
nRows = 0;
startRow = 1;
for i = 1:3
    nRows = floor(sizes(permutation(i)) * nRelevantFeatureRows);
    X = Xall(startRow : startRow + nRows - 1, :);
    currDate = dateXall(startRow : startRow + nRows - 1, :);
    y = yAll(startRow + featureInterval - 1 : startRow + featureInterval + nRows - 2, :);
    save("-mat-binary", sepFiles{permutation(i)}, "X", "y", "currDate"); 
    startRow = startRow + nRows + featureInterval - 1;
    printfNow("%s data saved for equity '%s'\n", sepNames{permutation(i)}, ticker);
endfor    

endfunction
