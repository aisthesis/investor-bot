## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} nnLearn (@var{params})
##
## Return and save @var{theta1}, @var{theta2}, optimal regularization parameter
## @var{lambda} and @var{cost} learned using a 3-layer (1 hidden layer) feedforward neural network with back-propagation.
##
## Parameters to be passed in @var{params}:
## Required;
## @itemize
## @item
## @code{params.weightsId} string corresponding to the identifier of the random initializer file. Example: "01"
## @item
## @code{params.trainFile} complete path to file containing training data. Example: 
## "splitadj/closes/train60xval20test20/train/features/256/labels/64/bullish/100pct/mean0/std100pct/combined.mat"
## Root is assumed to be root of predictor data, e.g. ./predictors/data/
## @item
## @code{params.nNeurons} number of neurons in hidden layer
## @end itemize
##
## Optional:
## @itemize
## @item
## @code{params.xvalFile} complete path to file containing cross-validation data. This parameter
## is required if more than 1 regularization parameter is to be tested. Example:
## "splitadj/closes/train60xval20test20/xval/features/256/labels/64/bullish/100pct/mean0/std100pct/combined.mat"
## @item
## @code{params.maxIter} maximum number of iterations to use. Defaults to 64.
## @item
## @code{params.nLambdas} number of lambdas to test for regularization. Defaults to 1.
## @item
## @code{params.lambdaSeed} first non-zero lambda to test. Defaults to 0. Setting this parameter to 0 potentially overrides
## overrides setting @code{params.nLambdas} to a value > 1.
## @end itemize
##
## Usage:
##
## @example
## [theta1, theta2, lambda, cost] = nnLearn(params);
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-21

function [theta1, theta2, lambda, cost] = nnLearn(params)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
weightsId = params.weightsId;
ofile = sprintf("output/learned%s.mat", weightsId);

% abort if parameters have already been learned
if exist(ofile, "file")
    printfNow("Values have already been learned. Delete file '%s' to relearn.\n", ofile);
    displayNow("Returning saved values.");
    load(ofile);
    return;
endif

nLambdas = 1;
lambdaSeed = 0;
if isfield(params, 'lambdaSeed') && params.lambdaSeed > 0 
    lambdaSeed = params.lambdaSeed;
    if isfield(params, 'nLambdas')
        nLambdas = params.nLambdas;
    endif
endif

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
lambdas = zeros(1, nLambdas);
lambdas(2:end) = lambdaSeed * (2 .^ [0:(nLambdas - 2)]');

ifTrain = sprintf("%s/%s", PREDICTOR_DATA_ROOT, params.trainFile);
ifXval = "";
if isfield(params, 'xvalFile')
    ifXval = sprintf("%s/%s", PREDICTOR_DATA_ROOT, params.xvalFile);
endif
nNeurons = params.nNeurons;
maxIter = 64;
if isfield(params, 'maxIter')
    maxIter = params.maxIter;
endif

displayNow("Loading training set");
load(ifTrain);
Xtrain = X;
ytrain = y;
nFeatures = size(Xtrain, 2);
options = optimset('Display', 'iter', 'GradObj', 'on', 'MaxIter', maxIter);
lambda = 0;

theta1init = csvread(sprintf("params/theta1init%s.csv", weightsId));
theta2init = csvread(sprintf("params/theta2init%s.csv", weightsId));
% unroll theta1 and theta2
nnParamsInit = [theta1init(:); theta2init(:)];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

createDir({"output"});
% no reguarization parameter
if nLambdas <= 1
    displayNow("Training neural network with no regularization");
    displayNow("Be patient: Run time can be several hours.");
    costFcn = @(p) nnCostFunction(p, nFeatures, nNeurons, 1, Xtrain, ytrain, lambdaSeed);
    [nnParams, cost] = fmincg(costFcn, nnParamsInit, options);
    displayNow("Training complete. Saving results.");
    theta1 = reshape(nnParams(1:nNeurons * (nFeatures + 1)), nNeurons, nFeatures + 1);
    theta2 = reshape(nnParams((1 + nNeurons * (nFeatures + 1)):end), 1, nNeurons + 1);
    save("-mat-binary", ofile, "theta1", "theta2", "lambda", "cost");
    return;
endif

% regularization
minCost = [];
bestJxval = -1;
bestLambda = 0;
bestNnParams = nnParamsInit;
displayNow("Loading cross-validation set");
load(ifXval);
Xxval = X;
yxval = y;

displayNow("Training neural network with regularization");
displayNow("Be patient: Run time can be several hours.");
for lamb = lambdas
    printfNow("Training using regularization parameter %.03f\n", lamb);
    costFcn = @(p) nnCostFunction(p, nFeatures, nNeurons, 1, Xtrain, ytrain, lamb);
    [nnParams, cost] = fmincg(costFcn, nnParamsInit, options);
    printfNow("Training complete using regularization parameter %.03f\n", lamb);
    j = nnCostOnly(nnParams, nFeatures, nNeurons, 1, Xxval, yxval);
    printfNow("Unbiased cost on cross-validation set: %f\n", j);
    if bestJxval < 0 || j < bestJxval
        minCost = cost;
        bestNnParams = nnParams;
        bestLambda = lamb;
        bestJxval = j;
    endif
endfor

printfNow("Best cost on cross-validation set: %f, best lambda: %.03f\n", bestJxval, bestLambda);
displayNow("Training complete. Saving results.");
nnParams = bestNnParams;
lambda = bestLambda;
cost = minCost;
theta1 = reshape(nnParams(1:nNeurons * (nFeatures + 1)), nNeurons, nFeatures + 1);
theta2 = reshape(nnParams((1 + nNeurons * (nFeatures + 1)):end), 1, nNeurons + 1);
save("-mat-binary", ofile, "theta1", "theta2", "lambda", "cost");

endfunction
