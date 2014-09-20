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
featureInterval = 256;
labelInterval = 64;
labelType = "bullish";
ratio = 1.0;
maxIter = 512;
lambdaSeed = 0.05;
nLambdas = 8;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
lambdas = zeros(1, nLambdas);
lambdas(2:end) = lambdaSeed * (2 .^ [0:(nLambdas - 2)]');

ifTrain = sprintf("%s/splitadj/closes/train60xval20test20/train/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, featureInterval, labelInterval, labelType, floor(ratio * 100));
ifXval = sprintf("%s/splitadj/closes/train60xval20test20/xval/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, featureInterval, labelInterval, labelType, floor(ratio * 100));
ofile = "output/learned.mat";

displayNow("Loading training set");
load(ifTrain);
m = size(X, 1);
Xtrain = [ones(m, 1), X];
n = size(Xtrain, 2);
ytrain = y;

displayNow("Loading cross-validation set");
load(ifXval);
m = size(X, 1);
Xxval = [ones(m, 1), X];
yxval = y;
displayNow("Training and cross-validation data loaded");

displayNow("Finding optimal theta and lambda using logistic regression");
initial_theta = zeros(n, 1);
options = optimset('GradObj', 'on', 'MaxIter', maxIter);
score = 0;
bestScore = 0;
lambda = 0;
bestLambda = 0;
bestTheta = zeros(n, 1);

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

displayNow("Learning complete. Saving optimal theta and lambda.");
createDir({"output"});
save("-mat-binary", ofile, "theta", "lambda");

endfunction
