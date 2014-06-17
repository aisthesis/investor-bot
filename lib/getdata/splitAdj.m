function [adjPrices] = splitAdj(prices, splitIndex, splitFactor)

% Given a vector of prices, the index corresponding to the day of the split,
% and the split factor (e.g. 2 for 2:1, 1.5 for 3:2, etc.), 
% return a vector of prices in which all values up to and including
% the split index are divided by the split factor.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

adjPrices = [prices(1:splitIndex, :) ./ splitFactor; prices(splitIndex + 1:end, :)];

end
