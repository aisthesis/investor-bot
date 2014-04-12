function saveSplitAdjCloses(splitAdjCloses, ticker)

% Given a vector of split adjusted closes and a ticker,
% save the vector in a binary file of the form
% ./data/ge-splitadjcloses.mat
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

PATH_TO_DATA = getenv("INVESTOR_BOT_DATA_PATH");
suffix = "-splitadjcloses.mat";
fileName = [PATH_TO_DATA ticker suffix];
closes = splitAdjCloses;

save("-mat-binary", fileName, "closes");

end
