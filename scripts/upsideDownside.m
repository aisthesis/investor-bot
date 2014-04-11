function [upside, downside, upToDownRatio] = upsideDownside(maxVal, minVal, currVal)

% Given a maxVal, minVal and currVal, return the relative upside 
% (i.e., not the absolute number but rather the upside relative to
% currVal), relative downside and the ratio of upside to downside.
%
% All values are guaranteed to be strictly > 0 to avoid division
% by zero issues. A 0 or negative value will be replaced with the 
% minimum value of 0.001.
%
% Author: Marshall Farrier
% Since: 2014-04-10
% 

MINIMUM = 0.001;
upside = max((maxVal - currVal) / currVal, MINIMUM);
downside = max((currVal - minVal) / currVal, MINIMUM);
upToDownRatio = upside / downside;

end
