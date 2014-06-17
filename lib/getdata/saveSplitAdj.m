function saveSplitAdj(splitAdjOhlc, ticker)

% Given split adjusted ohlc data for the given
% ticker, save it to a matlab binary file 
% also including dates, volumes, and adj closes,
% unadjusted from <ticker>.mat
%
% The file created will be named like:
% ./data/ge-splitadj.mat
%
% Author: Marshall Farrier
% Since: 2014-04-12
% 

PATH_TO_DATA = getenv("DATA_ROOT");
inFileSuffix = ".mat";
outFileSuffix = "-splitadj.mat";
inFileName = [PATH_TO_DATA ticker inFileSuffix];
outFileName = [PATH_TO_DATA ticker outFileSuffix];

load(inFileName);
opens = splitAdjOhlc(1:end, 1);
highs = splitAdjOhlc(1:end, 2);
lows = splitAdjOhlc(1:end, 3);
closes = splitAdjOhlc(1:end, 4);

save("-mat-binary", outFileName, "sessionDates", "opens", "highs", "lows", "closes", "volumes", "adjCloses");

end
