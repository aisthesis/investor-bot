function [labels] = getUpsideExceededLabels(prices, interval, minUpside)

% Given a price vector, an interval over which to measure
% the ratio of upside to downside, and a minimum required ratio, return a vector
% of classification labels with indices corresponding
% to the starting points of those intervals where the
% ratio of upside to downside meets or exceeds the specified
% minRatio.
%
% For example, suppose our interval is 30 and our minRatio
% is 2. The first price in our vector is $50. The maximum
% of the subsequent 30 prices is $55, and the minimum is $45.
% Then the ratio of upside ($5) to downside (also $5) is 1,
% and falls below the given minimum of 2.
% So, we put 0 for "no" as the first value in our labels
% vector.
%
% If instead, the maximum of the subsequent 30 prices were
% $60 and all other values unchanged, we would have instead
% put 1 for "yes" as the first value in the labels vector.
% Similarly for each entry in the prices vector, we
% will examine upside and downside over the next 30 entries
% and enter 0 or 1 in our result vector depending on whether
% or not the minimum ratio of upside to downside was achieved.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

rows = length(prices) - interval;
labels = zeros(rows, 1);
maxVal = 0;
minVal = 0;
currVal = 0;
upside = 0;

for i = 1:rows
    [maxVal, minVal, currVal] = futureExtrema(prices, i, interval);
    upside = upsideDownside(maxVal, minVal, currVal);
    if (upside >= minUpside)
        labels(i) = 1;
    endif
endfor

end
