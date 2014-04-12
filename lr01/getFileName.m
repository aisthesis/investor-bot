function [fileName] = getFileName(ticker, otherIdentifier, firstIndex, lastIndex)

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

% load each line as a string
lines = textread([PATH_TO_DATA ticker ".csv"], "%s");

% ignore header rows and capture first 10 characters as datestr
% Note that whitespace in 'Adj Close' makes header wrap to 2 lines
dates = strtrunc(lines(3:end), 10);
len = length(dates);

% extract desired dates and compose file name
startDate = datestr(dates(len - firstIndex + 1), "yyyymmdd");
endDate = datestr(dates(len - lastIndex + 1), "yyyymmdd");

fileName = [ticker "-" otherIdentifier "-" startDate "-" endDate ".mat"];

end
