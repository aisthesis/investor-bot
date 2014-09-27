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

displayNow("Loading training set");
load(ifTrain);
Xtrain = X;
ytrain = y;
options = optimset('MaxIter', maxIter);

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
    lambda = 0;
    save("-mat-binary", ofile, "theta1", "theta2", "lambda", "cost");
    return;
endif

% TODO
theta1 = [];
theta2 = [];
lambda = 0;
cost = 1;
return;
score = 0;
bestScore = 0;
lambda = 0;
bestLambda = 0;
bestTheta = zeros(n, 1);

% no regularization parameter
if nLambdas <= 1
    theta = fmincg(@(t)(lrCostFunction(t, Xtrain, ytrain)), initial_theta, options);
else
    displayNow("Loading cross-validation set");
    load(ifXval);
    m = size(X, 1);
    Xxval = [ones(m, 1), X];
    yxval = y;
    displayNow("Training and cross-validation data loaded");

    displayNow("Finding optimal theta and lambda using logistic regression");
    for lamb = lambdas
        theta = fmincg(@(t)(lrCostFunction(t, Xtrain, ytrain, lamb)), initial_theta, options);
        predicted = lrPredict(Xxval, theta);
        score = fscore(predicted, yxval);
        printfNow("lambda: %f, F1 score: %f\n", lamb, score);
        if score > bestScore
            bestScore = score;
            bestTheta = theta;
            bestLambda = lamb;
        endif
    endfor

    theta = bestTheta;
    lambda = bestLambda;
endif

displayNow("Learning complete. Saving optimal theta and lambda.");
createDir({"output"});
save("-mat-binary", ofile, "theta", "lambda");

endfunction
