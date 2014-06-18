## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} build (@var{featureInterval}, @var{labelInterval}, 
##      @var{bullMinRatio}, @var{upsideMinRatio}, @var{bearMaxRatio})
## Build features and labels for a group of equities, and separate
## training, cross-validation and test data sets. This is the generic build
## function allowing experimentation with various parameters.
##
## Features will consist of a row of @var{featureInterval} successive split-adjusted closes
## for each equity. The file saved will also include a parallel vector
## of datenums called currDate, which corresponds to the last date
## of the corresponding row.
##
## 3 types of labels will be saved:
## Bullish @var{bullMinRatio} in @var{labelInterval} days: 1 (yes) iff over the next @var{labelInterval} days, maxclose
## - currclose >= @var{bullMinRatio} * (currclose - minclose). This can be used as a signal
## to buy.
##
## Upside exceeded @var{upsideMinRatio} in @var{labelInterval} days: 1 (yes) iff over the next @var{labelInterval} days,
## maxclose >= @var{upsideMinRatio} * currclose. This can also be used as a signal to buy.
##
## Bearish @var{bearMaxRatio} in @var{labelInterval} dats: 1 (yes) iff over the next @var{labelInterval} days, maxclose
## - currclose <= @var{bearMaxRatio} * (currclose - minclose). Can be used as a signal to sell.
##
## Training set, cross-validation set and test set will be selected as
## random blocks from each equity on a 60-20-20 ratio (training-cv-test).
## The datasets will first be saved for each equity, then assembled into
## complete datasets including features and labels for all equities examined.
##
## Example usage:
## build(256, 64, 4.0, 1.25, 1.0);
##
## @strong{Caution:} don't run this function directly but instead
## create a script documenting the parameters used and then calling this function.
## @end deftypefn

## Author: mdf
## Created: 2014-06-17

function build(featureInterval, labelInterval, bullMinRatio, upsideMinRatio, bearMaxRatio)

displayNow("Loading equities to be analysed.");
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
inFile = "equities.csv";
equities = textread(sprintf("%s%s", PREDICTOR_DATA_ROOT, inFile), "%s");
n = size(equities, 1);

displayNow("================================================================");
displayNow("LABELS");
displayNow("Creating bearish labels");
for i = 1:n
    printfNow("Creating bearish labels for equity '%s'\n", equities{i});
    bearLabEquity(equities{i}, labelInterval, bearMaxRatio);
endfor
displayNow("Bearish labels created!\n");

displayNow("Creating bullish labels");
for i = 1:n
    printfNow("Creating bullish labels for equity '%s'\n", equities{i});
    bullLabEquity(equities{i}, labelInterval, bullMinRatio);
endfor
displayNow("Bullish labels created!\n");

displayNow("Creating upside-exceeded labels");
for i = 1:n
    printfNow("Creating upside-exceeded labels for equity '%s'\n", equities{i});
    upsExLabEquity(equities{i}, labelInterval, upsideMinRatio);
endfor
displayNow("Upside exceeded labels created!\n");

displayNow("================================================================");
displayNow("FEATURES");
displayNow("Creating features");

end
