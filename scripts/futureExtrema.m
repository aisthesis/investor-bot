function [maxVal, minVal, currVal] = futureExtrema(prices, index, interval)
% Given a vector of successive prices and an index corresponding
% to a point in time, extract the maximum price over the subsequent
% time period given by the input interval.
% Note that the interval tested will not include the
% current time, so it will sometimes occur that maxVal < currVal
% or minVal > currVal
%
% Author: Marshall Farrier
% Since: 2014-04-10
% 

rangeStart = index + 1;
rangeEnd = index + interval;
maxVal = max(prices(rangeStart:rangeEnd));
minVal = min(prices(rangeStart:rangeEnd));
currVal = prices(index);

end
