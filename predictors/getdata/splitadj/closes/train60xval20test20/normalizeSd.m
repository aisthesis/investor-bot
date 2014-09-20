## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{alreadyExists}=} normalizeSd (@var{labelType}, @var{labelMakerFcn}, @var{featureInterval}, @var{labelInterval}, 
##      @var{ratio})
## Build normalized features and labels for a group of equities.
## 
## Data is normalized so that the mean of each row of features is 0, and the standard
## deviation is 1. Otherwise,
## the data is the same as that created by build()
##
## Usage:
##
## @example
## alreadyExists = normalizeSd("bullish", @@bullLabEquity, 256, 64, 1.0);
## @end example
##
## @strong{Caution:} don't run this function directly but instead
## create a script documenting the parameters used and then calling this function.
## @end deftypefn

## Author: mdf
## Created: 2014-09-20

function alreadyExists = normalizeSd(labelType, labelMakerFcn, featureInterval, labelInterval, ratio)

% call normalizeMean to ensure that source data exists
normalizeMean(labelType, labelMakerFcn, featureInterval, labelInterval, ratio);

% construct normalized data
displayNow("Normalizing data by row to standard deviation 1");
alreadyExists = 1;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/splitadj/closes", PREDICTOR_DATA_ROOT);
sepNames = {"train" "xval" "test"};
nSepNames = length(sepNames);
sepOutPaths = {};
sepOutFiles = {};
path = {};

% get output file names and create directories as necessary
for i = 1:nSepNames
    path = {"train60xval20test20" sepNames{i} "features" sprintf("%d", featureInterval) "labels" sprintf("%d", labelInterval) ...
            labelType sprintf("%dpct", floor(ratio * 100)) "mean0" "std100pct"};
    sepOutPaths{i} = createDir(path, algoDataRoot);
    sepOutFiles{i} = sprintf("%s/%scombined.mat", algoDataRoot, sepOutPaths{i});
    alreadyExists = alreadyExists && exist(sepOutFiles{i}, "file");
endfor

if alreadyExists
    displayNow("Data normalized to std dev 1 already exists. Delete files to rebuild.");
    return;
endif

% get input file names
sepInPaths = {};
sepInFiles = {};
for i = 1:nSepNames
    sepInPaths{i} = sprintf("%s/train60xval20test20/%s/features/%d/labels/%d/%s/%dpct/mean0", ...
            algoDataRoot, sepNames{i}, featureInterval, labelInterval, labelType, floor(ratio * 100));
    sepInFiles{i} = sprintf("%s/combined.mat", sepInPaths{i});
endfor

% load each input file, normalize and save
stdXbyRow = [];
multiplier = [];
for i = 1:nSepNames
    load(sepInFiles{i});
    stdXbyRow = std(X, 0, 2);
    multiplier = 1 ./ stdXbyRow;
    X = bsxfun(@times, X, multiplier);
    save("-mat-binary", sepOutFiles{i}, "X", "y", "currDate");
    printfNow("Normalized data %s saved\n", sepNames{i});
endfor

displayNow("Data normalized to std dev 1 saved.");

endfunction
