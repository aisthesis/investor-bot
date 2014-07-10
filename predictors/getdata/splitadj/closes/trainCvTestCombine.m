## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} trainCvTestCombine (@var{labelType}, @var{equities}, @var{featureInterval},
## @var{labelInterval}, @var{ratio}) 
## Combine and store training, cross-validation and test datasets for the given label type and all equities
## in the cellarray @var{equities}.
## 
## Example usage:
##
## @example
## trainCvTestCombine('bullish', @{'cat'; 'dd'@}, 256, 64, 1.0);
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-06-19

function trainCvTestCombine(labelType, equities, featureInterval, labelInterval, ratio)

displayNow("trainCvTestCombine() called");
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
NAMES = {"train" "xval" "test"};
N_NAMES = length(NAMES);
nEquities = length(equities);
Xall = [];
datesAll = [];
yAll = [];
ofile = "";

for i = 1:N_NAMES
    ofile = sprintf("%s%s/features/%d/labels/%d/%s/%dpct/combined.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, labelType, floor(ratio * 100));

    if exist(ofile)
        printfNow("Skipping file %s because it already exists.\nDelete file and rerun this function to rebuild it.\n\n", ofile);
        continue;
    endif

    printfNow("Combining '%s' data.\n", NAMES{i});
    Xall = [];
    datesAll = [];
    yAll = [];
    for j = 1:nEquities
        printfNow(". ");
        load(sprintf("%s%s/features/%d/labels/%d/%s/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
            NAMES{i}, featureInterval, labelInterval, labelType, floor(ratio * 100), equities{j}));
        Xall = [Xall; X];
        datesAll = [datesAll; currDate];
        yAll = [yAll; y];
    endfor
    X = Xall;
    currDate = datesAll;
    y = yAll;
    save("-mat-binary", ofile, "X", "y", "currDate");

    displayNow("");
    printfNow("'%s' data saved.\n", NAMES{i});
endfor

end
