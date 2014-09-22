## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} learn ()
## Return and save @var{theta} and optimal regularization parameter
## @var{lambda} learned using logistic regression.
##
## Usage:
##
## @example
## [theta, lambda] = learn()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function [theta, lambda] = learn()

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
dataRootPath = "splitadj/closes/train60xval20test20";
featureInterval = 256;
labelInterval = 64;
labelType = "bullish";
ratio = 1.0;
maxIter = 512;
lambdaSeed = 0.05;
nLambdas = 8;
relearn = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[theta, lambda] = lrLearn(dataRootPath, labelType, featureInterval, labelInterval, ratio, maxIter, ...
        lambdaSeed, nLambdas, relearn);

endfunction
