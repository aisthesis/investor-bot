function [labels] = getBullishLabels(prices, interval, minRatio)

% Given a price matrix, an interval over which to measure
% the ratio of upside to downside, and a maximum allowed ratio, return a vector
% of classification labels with indices corresponding
% to the starting points of those intervals where the
% ratio of upside to downside falls at or below the specified
% maxRatio.

% Each row of prices are prices that occurred during a session.
% The row can be arbitrary length (typically 1 for a single
% parameter such as close, or 4 for ohlc).
%
% For example, suppose our interval is 30 and our maxRatio
% is 1. The first price in our vector is $50. The maximum
% of the subsequent 30 prices is $55, and the minimum is $45.
% Then the ratio of upside ($5) to downside (also $5) is 1,
% exactly the specified maximum.
% So, we put 1 for "yes" as the first value in our labels
% vector to indicate that this interval stays within
% the specified maximum.
%
% If instead, the maximum of the subsequent 30 prices were
% $60 and all other values unchanged, we would have instead
% put 0 for "no" as the first value in the labels vector.
% Similarly for each entry in the prices vector, we
% will examine upside and downside over the next 30 entries
% and enter 0 or 1 in our result vector depending on whether
% or not the ratio of upside to downside was at or below
% the specified maximum.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

rows = size(prices, 1) - interval;
labels = zeros(rows, 1);
maxVal = 0;
minVal = 0;
currVal = 0;
upToDownRatio = 0;

for i = 1:rows
    [maxVal, minVal, currVal] = futureExtrema(prices, i, interval);
    [~, ~, upToDownRatio] = upsideDownside(maxVal, minVal, currVal);
    if (upToDownRatio >= minRatio)
        labels(i) = 1;
    endif
endfor

end
