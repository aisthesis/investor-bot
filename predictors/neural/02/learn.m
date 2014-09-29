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
## [theta1, theta2, lambda, cost] = learn("01");
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function [theta1, theta2, lambda, cost] = learn(weightId)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
params = {};
params.weightsId = weightId;
params.trainFile = "splitadj/closes/train60xval20test20/train/features/256/labels/64/bullish/100pct/combined.mat";
params.nNeurons = csvread("params/neurons.csv");
params.maxIter = 64;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[theta1, theta2, lambda, cost] = nnLearn(params);

endfunction
