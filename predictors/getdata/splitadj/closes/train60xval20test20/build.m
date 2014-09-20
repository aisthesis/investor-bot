## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} build (@var{labelType}, @var{labelMakerFcn}, @var{featureInterval}, @var{labelInterval}, 
##      @var{ratio})
## Build features and labels for a group of equities, and separate
## training and test data sets. This is the generic build
## function allowing experimentation with various parameters.
##
## @var{labelMakerFcn} should accept an equity string, such as "ge", a label interval
## and a ratio. Using these parameters, it should create and save the appropriate
## labels.
##
## Features will consist of a row of @var{featureInterval} successive split-adjusted closes
## for each equity. The file saved will also include a parallel vector
## of datenums called currDate, which corresponds to the last date
## of the corresponding row.
##
## Training set, cross-validation set and test set will be selected as
## random blocks from each equity on a 60-20-20 ratio (training-cv-test).
## The datasets will first be saved for each equity, then assembled into
## complete datasets including features and labels for all equities examined.
##
## Usage:
##
## @example
## build("bullish", @@bullLabEquity, 256, 64, 1.0);
## @end example
##
## @strong{Caution:} don't run this function directly but instead
## create a script documenting the parameters used and then calling this function.
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function build(labelType, labelMakerFcn, featureInterval, labelInterval, ratio)

source('.octaverc');
displayNow("Loading equities to be analysed.");
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
path = "splitadj/closes";
inFile = sprintf("%s/%s/equities.csv", PREDICTOR_DATA_ROOT, path);
equities = textread(inFile, "%s");
nEquities = size(equities, 1);

displayNow("================================================================");
displayNow("LABELS");
filesExist = 1;
tmp = 0;
for i = 1:nEquities
    [~, tmp] = labelMakerFcn(equities{i}, labelInterval, ratio);
    filesExist = filesExist && tmp;
    if !tmp
        printfNow("Labels created for equity '%s'\n", equities{i});
    endif
endfor
if filesExist
    displayNow("Labels already exist. Delete files to rebuild.");
else
    displayNow("Labels created.\n");
endif

displayNow("================================================================");
displayNow("FEATURES");
filesExist = 1;
tmp = 0;
for i = 1:nEquities
    [~, tmp] = featuresEquity(equities{i}, featureInterval);
    filesExist = filesExist && tmp;
    if !tmp
        printfNow("Features created for equity '%s'\n", equities{i});
    endif
endfor
if filesExist
    displayNow("Features already exist. Delete files to rebuild.");
else
    displayNow("Features created!\n");
endif

displayNow("================================================================");
displayNow("TRAINING, CROSS-VALIDATION AND TEST DATA");
filesExist = 1;
tmp = 0;
for i = 1:nEquities
    tmp = trainXvTestEquity(labelType, equities{i}, featureInterval, labelInterval, ratio);
    filesExist = filesExist && tmp;
    if !tmp
        printfNow("Training, xval  and test data created for equity '%s'\n", equities{i});
    endif
endfor
tmp = trainXvTestCombine(labelType, equities, featureInterval, labelInterval, ratio);
filesExist = filesExist && tmp;
if filesExist
    displayNow("Training, xval and test data already exist. Delete files to rebuild.");
else
    displayNow("Training, xval and test data created!\n");
endif

end
