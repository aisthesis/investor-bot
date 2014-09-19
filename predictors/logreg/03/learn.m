## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{theta} =} learn ()
## Return and save @var{theta} learned using logistic regression.
##
## This algorithm doesn't use regularization on the hypothesis
## that its improvement of predictive power is negligible despite
## significant cost in runtime.
##
## Usage:
##
## @example
## theta = learn()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-19

function theta = learn()

% parameters used:
featureInterval = 256;
labelInterval = 64;
labelType = "bullish";
ratio = 1.0;
maxIter = 64;
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");

infile = sprintf("%s/train70test30/splitadj/closes/train/features/%d/labels/%d/%s/%dpct/combined.mat", ...
    PREDICTOR_DATA_ROOT, featureInterval, labelInterval, labelType, floor(ratio * 100));
ofile = "output/learned.mat";

displayNow("Loading training set");
load(infile);
displayNow("Training set loaded. Learning using logistic regression.");
m = size(X, 1);
Xtrain = [ones(m, 1), X];
n = size(Xtrain, 2);
ytrain = y;
initial_theta = zeros(n, 1);
options = optimset('GradObj', 'on', 'MaxIter', maxIter);
theta = fmincg(@(t)(lrCostFunction(t, Xtrain, ytrain)), initial_theta, options);
displayNow("Learning complete. Saving theta");
createDir({"output"});
save("-mat-binary", ofile, "theta");

endfunction
