function [X, y] = getTrainingSetAll(featureSetFile, featuresInterval, labelsFile, labelsInterval)

% Given fully qualified file names and the intervals used
% in each, generate a training set using all data in the files
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

% loads into `featureSets` matrix
load(featureSetFile);
% loads into `labels` vector
load(labelsFile);

X = featureSets(1:end-labelsInterval, :);
X = [ones(size(X, 1), 1) X];
y = labels(featuresInterval:end, :);

end
