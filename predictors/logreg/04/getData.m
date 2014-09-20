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

% parameters
algoName = "04";
labelType = "bullish";
labelMakerFcn = "bullLabEquity";
featureInterval = 256;
labelInterval = 64;
ratio = 1.0;

printfNow("Assembling data for logreg/%s\n", algoName);
% TODO create these functions in getdata/splitadj/closes/train60xval20test20:
% build(labelType, str2func(labelMakerFcn), featureInterval, labelInterval, ratio);
% normalizeMean(labelType, featureInterval, labelInterval, ratio);
% normalizeSd(labelType, featureInterval, labelInterval, ratio);
% while it's logicall possible to normalize sd without normalizing mean,
% it's hard to imagine why one would want to. So for now, this function
% will presuppose normalized mean.
% normalizeSd() will call normalizeMean(), which in turn will call build()
% to ensure that pre-requisites are built.

printfNow("Finished building data for logreg/%s\n", algoName); 

end
