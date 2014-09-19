## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{alreadyExists}=} trainTestEquity (@var{labelType}, @var{ticker}, @var{featureInterval},
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
## alreadyExists = trainTestEquity("bullish", "cat", 256, 64, 4.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function alreadyExists = trainTestEquity(labelType, ticker, featureInterval, labelInterval, ratio);

alreadyExists = 0;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/train70test30/splitadj/closes", PREDICTOR_DATA_ROOT);
trainPath = {"train" "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
    labelType sprintf("%dpct", floor(ratio * 100))};
testPath = {"test" "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
    labelType sprintf("%dpct", floor(ratio * 100))};
trainPathTxt = createDir(trainPath, algoDataRoot);
testPathTxt = createDir(testPath, algoDataRoot);
ofTrain = sprintf("%s/%s%s.mat", algoDataRoot, trainPathTxt, ticker);
ofTest = sprintf("%s/%s%s.mat", algoDataRoot, testPathTxt, ticker);

% return if both files already exist
if exist(ofTrain, "file") && exist(ofTest, "file")
    alreadyExists = 1;
    return;
endif

sizes = [0.7 0.3];
% get permutation for equity
permutationsFile = sprintf("%s/divisions-2.mat", algoDataRoot);
load(permutationsFile);
permutation = permutations.(ticker);

% load features
load(sprintf("%s/features/%d/%s.mat", algoDataRoot, featureInterval, ticker));
Xall = X;
dateXall = currDate;
nRelevantFeatureRows = size(Xall, 1) - featureInterval + 1 - labelInterval;

% load labels
load(sprintf("%s/labels/%d/%s/%dpct/%s.mat", algoDataRoot, labelInterval, labelType, ...
    floor(ratio * 100), ticker));
yAll = y;

% separate and save data sets
nRowsTrain = floor(sizes(1) * nRelevantFeatureRows);
nRowsTest = nRelevantFeatureRows - nRowsTrain;
startRowTrain = 1;
startRowTest = 1;
if permutation(1) == 1
    startRowTest = nRowsTrain + featureInterval;
else
    startRowTrain = nRowsTest + featureInterval;
endif

% save training set
X = Xall(startRowTrain : startRowTrain + nRowsTrain - 1, :);
currDate = dateXall(startRowTrain : startRowTrain + nRowsTrain - 1, :);
y = yAll(startRowTrain + featureInterval - 1 : startRowTrain + featureInterval + nRowsTrain - 2, :);
save("-mat-binary", ofTrain, "X", "y", "currDate");
printfNow("Training set saved for equity '%s'\n", ticker);

% save test set
X = Xall(startRowTest : startRowTest + nRowsTest - 1, :);
currDate = dateXall(startRowTest : startRowTest + nRowsTest - 1, :);
y = yAll(startRowTest + featureInterval - 1 : startRowTest + featureInterval + nRowsTest - 2, :);
save("-mat-binary", ofTest, "X", "y", "currDate");
printfNow("Test set saved for equity '%s'\n", ticker);

endfunction
