## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{alreadyExists}=} trainCvTestCombine (@var{labelType}, @var{equities}, @var{featureInterval},
## @var{labelInterval}, @var{ratio}) 
## Combine and store training and test datasets for the given label type and all equities
## in the cellarray @var{equities}.
## 
## Example usage:
##
## @example
## alreadyExists = trainTestCombine('bullish', @{'cat'; 'dd'@}, 256, 64, 1.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function alreadyExists = trainTestCombine(labelType, equities, featureInterval, labelInterval, ratio)

alreadyExists = 0;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/train70test30/splitadj/closes", PREDICTOR_DATA_ROOT);
trainPathTxt = sprintf("%s/train/features/%d/labels/%d/%s/%dpct", algoDataRoot, featureInterval, labelInterval, ...
    labelType, floor(ratio * 100));
testPathTxt = sprintf("%s/test/features/%d/labels/%d/%s/%dpct", algoDataRoot, featureInterval, labelInterval, ...
    labelType, floor(ratio * 100));
ofTrain = sprintf("%s/combined.mat", trainPathTxt);
ofTest = sprintf("%s/combined.mat", testPathTxt);

% return if both files already exist
if exist(ofTrain, "file") && exist(ofTest, "file")
    alreadyExists = 1;
    return;
endif

nEquities = length(equities);
Xall = [];
datesAll = [];
yAll = [];
infile = "";

% combined training data
displayNow("Creating combined training data. This may take a few minutes!");
for i = 1:nEquities
    infile = sprintf("%s/%s.mat", trainPathTxt, equities{i});
    load(infile);
    Xall = [Xall; X];
    datesAll = [datesAll; currDate];
    yAll = [yAll; y];
endfor
X = Xall;
currDate = datesAll;
y = yAll;
save("-mat-binary", ofTrain, "X", "y", "currDate");
displayNow("Combined training data saved.");

% combined test data
displayNow("Creating combined test data. This may take a few minutes!");
Xall = [];
datesAll = [];
yAll = [];
for i = 1:nEquities
    infile = sprintf("%s/%s.mat", testPathTxt, equities{i});
    load(infile);
    Xall = [Xall; X];
    datesAll = [datesAll; currDate];
    yAll = [yAll; y];
endfor
X = Xall;
currDate = datesAll;
y = yAll;
save("-mat-binary", ofTest, "X", "y", "currDate");
displayNow("Combined test data saved.");

endfunction
