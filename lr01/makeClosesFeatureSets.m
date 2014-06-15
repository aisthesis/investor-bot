function [featureSets] = makeClosesFeatureSets(ticker, interval)

% Given a ticker and an interval, make and save all available
% feature sets using split adjusted data.
%
% Author: Marshall Farrier
% Since: 2014-04-13
% 

PATH_TO_DATA = getenv("INVESTOR_BOT_DATA_PATH");
suffix = "-splitadj.mat";
inFile = [PATH_TO_DATA ticker suffix];
load(inFile);

featureSets = pricesToFeatureSets(closes, interval);
saveFeatureSets(featureSets, ticker, "splitadj-closes")

end
