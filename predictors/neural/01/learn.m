## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} learn ()
## Return and save @var{theta} and optimal regularization parameter
## @var{lambda} learned using a neural network. 
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
labelType = "bullish";
featureInterval = 256;
labelInterval = 64;
ratio = 1.0;
weightId = "01";
nNeurons = 12;
maxIter = 16;
lambdaSeed = 0.0;
nLambdas = 1;
relearn = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[theta, lambda] = nnLearn(dataRootPath, labelType, featureInterval, labelInterval, ratio, weightId, nNeurons,
        maxIter, lambdaSeed, nLambdas, relearn);

endfunction
