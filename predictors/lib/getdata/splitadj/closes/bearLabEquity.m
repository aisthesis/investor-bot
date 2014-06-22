function [y] = bearLabEquity(ticker, interval, maxRatio)

% Given a ticker, an interval, and a maximum ratio, return and save
% labels for all available data.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

INFILE_ROOT = getenv("DATA_ROOT");
INFILE_SUFFIX = "-splitadj.mat";
OUTFILE_ROOT = getenv("PREDICTOR_DATA_ROOT");
path = {"labels" sprintf("%d", interval) "bearish" sprintf("%dpct", floor(maxRatio * 100))}; 
pathTxt = createDir(path, OUTFILE_ROOT);
OUTFILE_SUFFIX = ".mat";

inFile = sprintf("%s%s%s", INFILE_ROOT, ticker, INFILE_SUFFIX);
load(inFile);
y = getBearishLabels(closes, interval, maxRatio);
currDate = sessionDates(1:end - interval);

outFile = sprintf("%s%s%s%s", OUTFILE_ROOT, pathTxt, ticker, OUTFILE_SUFFIX);
save("-mat-binary", outFile, "y", "currDate");

end
