## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} trainCvTestCombine (@var{equities}, @var{featureInterval},
## @var{labelInterval}, @var{bullMinRatio}, @var{upsideMinRatio}, @var{bearMaxRatio})
## Combine and store training, cross-validation and test datasets all equities
## in the cellarray @var{equities}.
## 
## Example usage:
## trainCvTestCombine({'cat'; 'dd'}, 256, 64, 4.0, 1.25, 1.0);
## @end deftypefn

## Author: mdf
## Created: 2014-06-19

function trainCvTestCombine(equities, featureInterval, labelInterval, bullMinRatio, upsideMinRatio, bearMaxRatio);

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
NAMES = {"train" "xval" "test"};
N_NAMES = length(NAMES);
nEquities = length(equities);
Xall = [];
datesAll = [];
yAll = [];

for i = 1:N_NAMES
    printfNow("Combining '%s' data.\n", NAMES{i});
    Xall = [];
    datesAll = [];
    yAll = [];
    for j = 1:nEquities
        printfNow(". ");
        load(sprintf("%s%s/features/%d/labels/%d/bullish/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
            NAMES{i}, featureInterval, labelInterval, floor(bullMinRatio * 100), equities{j}));
        Xall = [Xall; X];
        datesAll = [datesAll; currDate];
        yAll = [yAll; y];
    endfor
    X = Xall;
    currDate = datesAll;
    y = yAll;
    save("-mat-binary", sprintf("%s%s/features/%d/labels/%d/bullish/%dpct/combined.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, floor(bullMinRatio * 100)), "X", "y", "currDate");

    Xall = [];
    datesAll = [];
    yAll = [];
    for j = 1:nEquities
        printfNow(". ");
        load(sprintf("%s%s/features/%d/labels/%d/bearish/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
            NAMES{i}, featureInterval, labelInterval, floor(bearMaxRatio * 100), equities{j}));
        Xall = [Xall; X];
        datesAll = [datesAll; currDate];
        yAll = [yAll; y];
    endfor
    X = Xall;
    currDate = datesAll;
    y = yAll;
    save("-mat-binary", sprintf("%s%s/features/%d/labels/%d/bearish/%dpct/combined.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, floor(bearMaxRatio * 100)), "X", "y", "currDate");

    Xall = [];
    datesAll = [];
    yAll = [];
    for j = 1:nEquities
        printfNow(". ");
        load(sprintf("%s%s/features/%d/labels/%d/upside-exceeded/%dpct/%s.mat", PREDICTOR_DATA_ROOT, ...
            NAMES{i}, featureInterval, labelInterval, floor((upsideMinRatio - 1) * 100), equities{j}));
        Xall = [Xall; X];
        datesAll = [datesAll; currDate];
        yAll = [yAll; y];
    endfor
    X = Xall;
    currDate = datesAll;
    y = yAll;
    save("-mat-binary", sprintf("%s%s/features/%d/labels/%d/upside-exceeded/%dpct/combined.mat", PREDICTOR_DATA_ROOT, ...
        NAMES{i}, featureInterval, labelInterval, floor((upsideMinRatio - 1) * 100)), "X", "y", "currDate");

    displayNow("");
    printfNow("'%s' data saved.\n", NAMES{i});
endfor

end
