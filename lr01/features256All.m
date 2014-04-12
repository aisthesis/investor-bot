function [featureSets] = features256All(ticker)

% Given a ticker, return and save all available
% data as sets of 256 features.
% The file will be saved in the ./features/ subdirectory
% with a name like 'ge-256-19620101-20140409.mat'.
% The name specifies the ticker, number of features (days)
% and the start and end dates for the feature set.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

SAVE_PATH = "./features/";

closes = getYahooCol(ticker);
featureSets = getFeatureSets(closes, 256);

fileName = getFileName(ticker, "256", 1, length(closes));
fileName = [SAVE_PATH fileName];

save("-mat-binary", fileName, "featureSets");

end
