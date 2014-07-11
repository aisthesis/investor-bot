## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} setParams ()
## Set parameters to be used in the current predictor algorithm.
## Parameters will be saved to params.mat in the current directory.
##
## @itemize @bullet
## @item
## Setting @code{maxIter} to 64 seems to be plenty. 
## 
## @itemize @minus
## @item
## 64 results
## in a best F1 score of 71.3pct vs. a best F1 score of 71.4pct
## using 32. So the difference is clearly due primarily to noise.
##
## @item
## Although the best F1 score is actually slightly better using
## 32 iterations, the scores are more tightly distributed using
## 64. So the latter seems a reasonable choice, and the runtime
## isn't excessive.
## @end itemize
## 
## @end itemize
##
## Usage:
##
## @example
## setParams()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-02

function setParams()
    ofname = "params.mat";
    maxIter = 64;
    labelType = "bullish";
    labelMakerFcn = "bullLabEquity";
    featureInterval = 256;
    labelInterval = 64;
    ratio = 1.0;

    save("-mat-binary", ofname, "maxIter", "labelType", "labelMakerFcn", "featureInterval", "labelInterval", "ratio");

end
