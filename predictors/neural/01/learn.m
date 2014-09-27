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
## [theta1, theta2, lambda] = learn()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function [theta1, theta2, lambda] = learn()

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
dataRootPath = "splitadj/closes/train60xval20test20";
labelType = "bullish";
featureInterval = 256;
labelInterval = 64;
ratio = 1.0;
weightId = "02";
nFeatures = featureInterval;
nNeurons = 12;
maxIter = 4;
lambdaSeed = 0.0;
nLambdas = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[theta1, theta2, lambda] = nnLearn(dataRootPath, labelType, featureInterval, labelInterval, ratio, weightId, nFeatures, nNeurons, ...
        maxIter, lambdaSeed, nLambdas);

endfunction
