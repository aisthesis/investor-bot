function [featureSets] = getFeatureSets(prices, interval)

% Given a vector of successive prices and an
% interval specifying how many elements should be considered
% as a feature set, return all prices over the given interval
% as a row of the output matrix. Each row provides data
% incremented by one time unit (normally a day).

% For example, if the first row provides prices from
% 2013-03-01 to 2014-03-01, the next row will show prices from
% 2013-03-02 to 2014-03-02
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

rows = length(prices) - interval + 1;
featureSets = zeros(rows, interval);

for i = 1:interval
    featureSets(1:rows, i) = prices(i:(i + rows - 1));
endfor

end
