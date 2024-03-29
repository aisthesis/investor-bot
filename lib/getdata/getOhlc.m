function [ohlc, sessionDates] = getOhlc(ticker)

% Return a matrix of the unadjusted OHLC values for the given
% ticker. Retrieves whatever is present in <ticker>.mat
%
% Author: Marshall Farrier
% Since: 2014-04-12
% 

PATH_TO_DATA = getenv("DATA_ROOT");
suffix = ".mat";
fileName = [PATH_TO_DATA ticker suffix];

load(fileName);
ohlc = [opens highs lows closes];

end
