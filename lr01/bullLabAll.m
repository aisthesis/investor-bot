function [labels] = bullLabAll(ticker, interval, minRatio)

% Given a ticker, an interval, and a minimum ratio, return and save
% labels for all available data.
%
% The file will be saved in the ./bullish-labels/ subdirectory
% with a name like 'ge-64-400pct-19620101-20140409.mat'
% The name specifies the ticker, number of days over which
% to check the ratio of upside to downside, the minimum
% ratio required for success, and the date range.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

SAVE_PATH = "./bullish-labels/";
closes = getYahooCol(ticker);
labels = getBullishLabels(closes, interval, minRatio);

ratioPct = floor(minRatio * 100);
otherIdentifier = [sprintf("%d-%d", interval, ratioPct) "pct"];
fileName = getFileName(ticker, otherIdentifier, 1, length(closes));
fileName = [SAVE_PATH fileName];

save("-mat-binary", fileName, "labels");

end
