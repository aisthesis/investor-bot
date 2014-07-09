## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} build (@var{labelMakerFcn}, @var{featureInterval}, @var{labelInterval}, 
##      @var{ratio})
## Build features and labels for a group of equities, and separate
## training, cross-validation and test data sets. This is the generic build
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
## build(@@bullLabEquity, 256, 64, 1.0);
## @end example
##
## @strong{Caution:} don't run this function directly but instead
## create a script documenting the parameters used and then calling this function.
## @end deftypefn

## Author: mdf
## Created: 2014-06-17

function build(labelMakerFcn, featureInterval, labelInterval, ratio)

source('.octaverc');
displayNow("Loading equities to be analysed.");
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
inFile = "equities.csv";
equities = textread(sprintf("%s%s", PREDICTOR_DATA_ROOT, inFile), "%s");
n = size(equities, 1);

displayNow("================================================================");
displayNow("LABELS");
displayNow("Creating labels");
for i = 1:n
    printfNow("Creating bearish labels for equity '%s'\n", equities{i});
    labelMakerFcn(equities{i}, labelInterval, ratio);
endfor
displayNow("Label creation complete!\n");


displayNow("================================================================");
displayNow("FEATURES");
displayNow("Creating features");
for i = 1:n
    printfNow("Creating features for equity '%s'\n", equities{i});
    featuresEquity(equities{i}, featureInterval);
endfor
displayNow("Features created!\n");

displayNow("================================================================");
displayNow("TRAINING, CROSS-VALIDATION, TEST DATA");
displayNow("Creating training, cross-validation and test datasets");
for i = 1:n
    printfNow("Creating datasets for equity '%s'\n", equities{i});
    trainCvTestEquity(equities{i}, featureInterval, labelInterval, bullMinRatio, upsideMinRatio, bearMaxRatio);
endfor

displayNow("Combining datasets for all equities.");
trainCvTestCombine(equities, featureInterval, labelInterval, bullMinRatio, upsideMinRatio, bearMaxRatio);
displayNow("Training, cross-validation and test datasets created!\n");

displayNow("Done!");

end
