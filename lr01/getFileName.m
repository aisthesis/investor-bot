function [fileName] = getFileName(ticker, otherIdentifier, firstIndex, lastIndex, suffix = "mat")

% Given a ticker, an interval string, the first index to use
% and the last index to use, generates the name to 
% be used for the corresponding feature file.
% For example: 'ge-256-19620101-20140409.mat'.
% The name specifies the ticker, number of features (days)
% and the start and end dates for the feature set.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

PATH_TO_DATA = getenv("INVESTOR_BOT_DATA_PATH");

inFileName = [PATH_TO_DATA ticker ".mat"];
load(inFileName);

startDate = datestr(sessionDates(firstIndex), "yyyymmdd");
endDate = datestr(sessionDates(lastIndex), "yyyymmdd");

fileName = [ticker "-" otherIdentifier "-" startDate "-" endDate "." suffix];

end
