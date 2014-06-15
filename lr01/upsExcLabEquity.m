function [labels] = upsExcLabEquity(ticker, interval, minUpside)

% Given a ticker, an interval, and a minimum upside, return and save
% labels for all available data.
%
% The file will be saved in the ./upside-exceeded-labels/ subdirectory
% with a name like 'ge-64-25pct-19620101-20140409.mat'
% The name specifies the ticker, number of days over which
% to check the ratio of upside to downside, the maximum
% ratio required for success, and the date range.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

PATH_TO_DATA = getenv("INVESTOR_BOT_DATA_PATH");
INFILE_SUFFIX = "-splitadj.mat";
SAVE_PATH = "./upside-exceeded-labels/";

inFile = [PATH_TO_DATA ticker INFILE_SUFFIX];
load(inFile);
labels = getUpsideExceededLabels(closes, interval, minUpside);

ratioPct = floor(minUpside * 100);
otherIdentifier = [sprintf("%d-%d", interval, ratioPct) "pct"];
outFile = getFileName(ticker, otherIdentifier, 1, length(closes) - interval);
outFile = [SAVE_PATH outFile];

save("-mat-binary", outFile, "labels");

end
