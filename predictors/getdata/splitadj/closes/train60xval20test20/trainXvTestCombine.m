## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{alreadyExists}=} trainXvTestCombine (@var{labelType}, @var{equities}, @var{featureInterval},
## @var{labelInterval}, @var{ratio}) 
## Combine and store training and test datasets for the given label type and all equities
## in the cellarray @var{equities}.
## 
## Example usage:
##
## @example
## alreadyExists = trainXvTestCombine('bullish', @{'cat'; 'dd'@}, 256, 64, 1.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function alreadyExists = trainXvTestCombine(labelType, equities, featureInterval, labelInterval, ratio)

alreadyExists = 1;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/splitadj/closes", PREDICTOR_DATA_ROOT);
sepNames = {"train" "xval" "test"};
nSepNames = length(sepNames);
sepPaths = {};
sepOutFiles = {};
for i = 1:nSepNames
    sepPaths{i} = sprintf("%s/train60xval20test20/%s/features/%d/labels/%d/%s/%dpct", ...
            algoDataRoot, sepNames{i}, featureInterval, labelInterval, labelType, floor(ratio * 100));
    sepOutFiles{i} = sprintf("%s/combined.mat", sepPaths{i});
    alreadyExists = alreadyExists && exist(sepOutFiles{i}, "file");
endfor

% return if files already exist
if alreadyExists
    return;
endif

nEquities = length(equities);
infile = "";

% combine data of each type
for i = 1:nSepNames
    Xall = [];
    datesAll = [];
    yAll = [];
    printfNow("Creating combined %s data. This may take a few minutes!\n", sepNames{i});
    for j = 1:nEquities
        infile = sprintf("%s/%s.mat", sepPaths{i}, equities{j});
        load(infile);
        Xall = [Xall; X];
        datesAll = [datesAll; currDate];
        yAll = [yAll; y];
    endfor
    X = Xall;
    currDate = datesAll;
    y = yAll;
    save("-mat-binary", sepOutFiles{i}, "X", "y", "currDate");
    printfNow("Combined data %s saved.\n", sepNames{i});
endfor

endfunction
