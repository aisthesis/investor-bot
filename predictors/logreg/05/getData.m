## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} getData ()
## Generate the data sets needed to run the current machine learning
## algorithm.
##
## Usage:
##
## @example
## getData()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function getData()

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
algoName = "05";
labelType = "bullish";
labelMakerFcn = "bullLabEquity";
featureInterval = 256;
labelInterval = 64;
ratio = 1.0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

printfNow("Assembling data for logreg/%s\n", algoName);
normalizeMean(labelType, str2func(labelMakerFcn), featureInterval, labelInterval, ratio);
printfNow("Finished building data for logreg/%s\n", algoName); 

end
