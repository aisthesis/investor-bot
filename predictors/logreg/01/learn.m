## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} learn ()
## Return and save @var{theta} learned using logistic regression and the 
## regularization parameter @var{lambda} used to find theta.
##
## @var{lambda} is optimized to minimize F1 score.
##
## Usage:
##
## @example
## [theta, lambda] = learn()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-09

function learn()
    
    score = 0;
    bestScore = 0;
    lambda = 0;
    bestLambda = 0;
    ofname = "learned.mat";

    % ================================================================
    % Choices for regularization parameter
    nLambdas = 12;
    % Starting with this increment, lambda is successively increased by a factor of 2 
    lambdaIncrement = 0.001;
    lambdas = zeros(1, nLambdas);
    % lambdas = [0 0.001 0.002 0.004 etc.]
    lambdas(2:end) = lambdaIncrement * (2 .^ [0:(nLambdas - 2)]');

    % ================================================================
    % Get data
    load("params.mat");
    PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
    
    % training data
    displayNow("Loading training data");
    load(sprintf("%strain/features/%d/labels/%d/%s/%dpct/combined.mat", PREDICTOR_DATA_ROOT, ...
        featureInterval, labelInterval, labelType, floor(ratio * 100)));
    m = size(X, 1);
    Xtrain = [ones(m, 1), X];
    n = size(Xtrain, 2);
    ytrain = y;

    % cross-validation data
    displayNow("Loading cross-validation data");
    load(sprintf("%sxval/features/%d/labels/%d/%s/%dpct/combined.mat", PREDICTOR_DATA_ROOT, ...
        featureInterval, labelInterval, labelType, floor(ratio * 100)));
    m = size(X, 1);
    Xxval = [ones(m, 1), X];
    yxval = y;
    predicted = zeros(size(yxval));

    % ================================================================ 
    % find theta for each choice of lambda and choose the best
    initial_theta = zeros(n, 1);
    bestTheta = zeros(n, 1);
    options = optimset('GradObj', 'on', 'MaxIter', maxIter);
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

    % ================================================================
    % Set return values
    theta = bestTheta;
    lambda = bestLambda;

    % ================================================================
    % Save results
    save("-mat-binary", ofname, "theta", "lambda");

endfunction
