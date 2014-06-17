function [index] = dateToIndex(ticker, formattedDate)

% Return the index for data on the given ticker
% for the given formatted date
%
% Author: Marshall Farrier
% Since: 2014-04-12
% 

PATH_TO_DATA = getenv("DATA_ROOT");
suffix = ".mat";
fileName = [PATH_TO_DATA ticker suffix];

load(fileName);
datenumToFind = datenum(formattedDate);
index = find(sessionDates == datenumToFind);

end
