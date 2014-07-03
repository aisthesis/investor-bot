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
## Example usage:
## setParams()
## @end deftypefn

## Author: mdf
## Created: 2014-07-02

function setParams()
    ofname = "params.mat";
    maxIter = 5;
    featureInterval = 256;
    labelInterval = 64;
    bullMinRatio = 4.0;
    upsideMinRatio = 1.25;
    bearMaxRatio = 1.0;

    save("-mat-binary", ofname, "maxIter", "featureInterval", "labelInterval", ...
        "bullMinRatio", "upsideMinRatio", "bearMaxRatio");

end
