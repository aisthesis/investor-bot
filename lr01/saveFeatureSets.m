function saveFeatureSets(featureSets, ticker, identifier)

% Given a matrix of feature set (which should NOT include the constant
% feature 1), a ticker, and an identifier string, save
% the feature sets to a matlab binary file.
%
% The identifier string will be used in the file name to describe
% the parameter used for the feature sets (e.g., "splitadj-closes").
%
% The feature sets will then be saved as something like:
% ./features/ge-256-splitadj-closes-19620101-20140409.mat
% where 256 represents the interval used for the features
% (a feature value such as closing price for each day) and
% 19620101-20140409 represents the date range included
% in the feature set.
%
% The data ranges represent the date for the LAST VALUE
% IN EACH ROW of the feature set--i.e., the "current day"
% from the algorithm's point of view. So, each feature set
% includes a backlog of data prior to the first date given
% in the date range.
%
% Note that the date range is derived from querying the 
% complete data file on the given ticker, so it will be inaccurate
% if the featureSets used as input include only part of this data.
%
% Author: Marshall Farrier
% Since: 2014-04-13
% 

SAVE_PATH = "./features/";

numFeatures = size(featureSets, 2);
completeIdentifier = [sprintf("%d", numFeatures) "-" identifier];

fileName = getFileName(ticker, completeIdentifier, numFeatures, size(featureSets, 1) + numFeatures - 1);
fileName = [SAVE_PATH fileName];

save("-mat-binary", fileName, "featureSets");

end
