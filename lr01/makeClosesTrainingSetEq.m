function [X, y] = makeClosesTrainingSetEq(ticker, featureInterval, labelType, labelInterval, labelVal)

% Using the inputs, retrieve feature sets and labels for the given ticker,
% generate the corresponding training sets, return them and save them to file.
%
% Author: Marshall Farrier
% Since: 2014-04-14
% 

featureType = "splitadj-closes";

% get relevant dates
PATH_TO_DATA = getenv("INVESTOR_BOT_DATA_PATH");
suffix = "-splitadj.mat";
inFile = [PATH_TO_DATA ticker suffix];
load(inFile);
indices = struct ("featuresStart", featureInterval, ...
    "featuresEnd", size(sessionDates, 1), ...
    "labelsStart", 1, ...
    "labelsEnd", size(sessionDates, 1) - labelInterval);

% get input feature sets file name
FEATURE_SETS_PATH = "./features/";
fileIdentifier = sprintf("%d-splitadj-closes", featureInterval);
featuresFile = getFileName(ticker, fileIdentifier, indices.featuresStart, indices.featuresEnd);
featuresFile = [FEATURE_SETS_PATH featuresFile];

% get input labels file name
LABELS_PATH = ["./" labelType "-labels/"];
pctVal = floor(labelVal * 100);
fileIdentifier = [sprintf("%d-%d", labelInterval, pctVal) "pct"];
labelsFile = getFileName(ticker, fileIdentifier, indices.labelsStart, indices.labelsEnd);
labelsFile = [LABELS_PATH labelsFile];

% construct and save training set
[X, y] = getTrainingSetAll(featuresFile, featureInterval, labelsFile, labelInterval);
saveTrainingSetEq(X, y, ticker, featureType, labelType, labelInterval, labelVal);

end
