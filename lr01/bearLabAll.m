function bearLabAll(interval, maxRatio)

% Given a an interval, and a minimum ratio, save (in a separate file for each equity)
% labels for all available data on all equities.
%
% The file will be saved in the ./bullish-labels/ subdirectory
% with a name like 'ge-64-400pct-19620101-20140409.mat'
% The name specifies the ticker, number of days over which
% to check the ratio of upside to downside, the minimum
% ratio required for success, and the date range.
%
% Author: Marshall Farrier
% Since: 2014-04-13
% 

equities = { "cat", "dd", "f", "ge", "ibm", "jnj", "jpm", "xom" };
for i = 1:length(equities)
    bearLabEquity(equities{i}, interval, maxRatio);
endfor

end
