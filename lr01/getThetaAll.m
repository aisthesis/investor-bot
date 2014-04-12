function [theta] = getThetaAll(featureSetFile, featuresInterval, labelsFile, labelsInterval)

% Given fully qualified file names and the intervals used in each,
% return the optimal value of theta to use in logistic regression.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

[X, y] = getTrainingSetAll(featureSetFile, featuresInterval, labelsFile, labelsInterval);
theta = getTheta(X, y);

end
