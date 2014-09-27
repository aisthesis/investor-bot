## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} nnLearn (@var{dataRootPath}, @var{labelType}, @var{featureInterval},
## @var{labelInterval}, @var{ratio}, @var{weightsId}, @var{nFeatures}, @var{nNeurons}, @var{maxIter}, 
## @var{lambdaSeed}, @var{nLambdas}) 
##
## Return and save @var{theta} and optimal regularization parameter
## @var{lambda} learned using a 3-layer (1 hidden layer) feedforward neural network with back-propagation.
##
## Usage:
##
## @example
## [theta1, theta2, lambda, cost] = nnLearn("splitadj/closes/train60xval20test20", "bullish", 256, 64, 1.0, "01", 256, 60, 64, 0.05, 8);
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-21

function [theta1, theta2, lambda, cost] = nnLearn(dataRootPath, labelType, featureInterval, labelInterval, ratio, weightsId, nFeatures, nNeurons, ...
        maxIter = 16, lambdaSeed = 0.1, nLambdas = 1)

ofile = sprintf("output/learned%s.mat", weightsId);
if exist(ofile, "file")
    printfNow("Values have already been learned. Delete file '%s' to relearn.\n", ofile);
    displayNow("Returning saved values.");
    load(ofile);
    return;
endif

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
lambdas = zeros(1, nLambdas);
lambdas(2:end) = lambdaSeed * (2 .^ [0:(nLambdas - 2)]');

ifTrain = sprintf("%s/%s/train/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, dataRootPath, featureInterval, labelInterval, labelType, floor(ratio * 100));
ifXval = sprintf("%s/%s/xval/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, dataRootPath, featureInterval, labelInterval, labelType, floor(ratio * 100));
createDir({"output"});

displayNow("Loading training set");
load(ifTrain);
Xtrain = X;
ytrain = y;
options = optimset('MaxIter', maxIter);
lambda = 0;

theta1init = csvread(sprintf("params/theta1init%s.csv", weightsId));
theta2init = csvread(sprintf("params/theta2init%s.csv", weightsId));
% unroll theta1 and theta2
nnParamsInit = [theta1init(:); theta2init(:)];

% no reguarization parameter
if nLambdas <= 1
    displayNow("Training neural network with no regularization");
    displayNow("Be patient: Run time can be several hours.");
    costFcn = @(p) nnCostFunction(p, nFeatures, nNeurons, 1, Xtrain, ytrain, 0);
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
