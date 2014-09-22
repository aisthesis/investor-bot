## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{alreadyExists}=} normalizeSdEquities (@var{dataRootPath}, @var{featureInterval})
## Build normalized features for all relevant equities.
## 
## Data is normalized so that the mean of each row of features is 0 and the standard deviation is 1. Otherwise,
## the data is the same as that created by build()
##
## Usage:
##
## @example
## alreadyExists = normalizeSdEquities("splitadj/closes", 256);
## @end example
##
## @strong{Caution:} don't run this function directly but instead
## create a script documenting the parameters used and then calling this function.
## @end deftypefn

## Author: mdf
## Created: 2014-09-21

function alreadyExists = normalizeSdEquities(dataRootPath, featureInterval)

% get data to be normalized
displayNow("Normalizing data by row to standard deviation 1");
alreadyExists = 1;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
algoDataRoot = sprintf("%s/%s", PREDICTOR_DATA_ROOT, dataRootPath);
equities = textread(sprintf("%s/equities.csv", algoDataRoot), "%s");
nEquities = size(equities, 1);
ofile = "";
infile = "";

% determine whether files already exist
for i = 1:nEquities
    ofile = sprintf("%s/features/%d/mean0/std100pct/%s.mat", algoDataRoot, featureInterval, equities{i});
    alreadyExists = alreadyExists && exist(ofile, "file");
endfor

if alreadyExists
    displayNow("Data normalized to std dev 1 already exists. Delete files to rebuild.");
    return;
endif

% files don't exist so create them
createDir({"std100pct"}, sprintf("%s/features/%d/mean0", algoDataRoot, featureInterval));
stdXbyRow = [];
multiplier = [];
for i = 1:nEquities
    infile = sprintf("%s/features/%d/mean0/%s.mat", algoDataRoot, featureInterval, equities{i});
    ofile = sprintf("%s/features/%d/mean0/std100pct/%s.mat", algoDataRoot, featureInterval, equities{i});
    load(infile);
    stdXbyRow = std(X, 0, 2);
    multiplier = 1 ./ stdXbyRow;
    X = bsxfun(@times, X, multiplier);
    save("-mat-binary", ofile, "X", "currDate");
endfor

displayNow("Equity data normalized to std dev 1 saved.");

endfunction
