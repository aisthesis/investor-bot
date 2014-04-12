function [theta] = getThetaAll(featureSetFile, featuresInterval, labelsFile, labelsInterval)

% Given fully qualified file names and the intervals used in each,
% return the optimal value of theta to use in logistic regression.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

[X, y] = getTrainingSetAll(featureSetFile, featuresInterval, labelsFile, labelsInterval);
n = size(X, 2);
initial_theta = zeros(n, 1);
options = optimset('GradObj', 'on', 'MaxIter', 50);

theta = fmincg(@(t)(lrCostFunction(t, X, y)), initial_theta, options);

end
