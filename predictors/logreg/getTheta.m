function [theta] = getTheta(X, y, maxIter = 50)

% Given a training set with features X and labels y,
% return the optimal value of theta to use in logistic regression.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

n = size(X, 2);
initial_theta = zeros(n, 1);
% 100 iterations decreases cost minimally on the sample set I tried
options = optimset('GradObj', 'on', 'MaxIter', maxIter);

theta = fmincg(@(t)(lrCostFunction(t, X, y)), initial_theta, options);

end
