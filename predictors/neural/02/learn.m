## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} learn (@var{weightId})
## Return and save @var{theta} and optimal regularization parameter
## @var{lambda} learned using a neural network. 
##
## Usage:
##
## @example
## [theta1, theta2, lambda] = learn("01");
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function [theta1, theta2, lambda] = learn(weightId)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
dataRootPath = "splitadj/closes/train60xval20test20";
labelType = "bullish";
featureInterval = 256;
labelInterval = 64;
ratio = 1.0;
nFeatures = featureInterval;
nNeurons = csvread("params/neurons.csv");
maxIter = 64;
lambdaSeed = 0.5;
nLambdas = 1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[theta1, theta2, lambda] = nnLearn(dataRootPath, labelType, featureInterval, labelInterval, ratio, weightId, nFeatures, nNeurons, ...
        maxIter, lambdaSeed, nLambdas);

endfunction