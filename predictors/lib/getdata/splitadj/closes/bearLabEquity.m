function [labels] = bearLabEquity(ticker, interval, maxRatio)

% Given a ticker, an interval, and a maximum ratio, return and save
% labels for all available data.
%
% The file will be saved in the ./bearish-labels/ subdirectory
% with a name like 'ge-64-100pct-19620101-20140409.mat'
% The name specifies the ticker, number of days over which
% to check the ratio of upside to downside, the maximum
% ratio required for success, and the date range.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

INFILE_ROOT = getenv("DATA_ROOT");
INFILE_SUFFIX = "-splitadj.mat";
OUTFILE_ROOT = getenv("PREDICTOR_DATA_ROOT");
path = {"labels" sprintf("%d", interval) "bearish" sprintf("%dpct", floor(maxRatio * 100))}; 
pathTxt = createDir(path, OUTFILE_ROOT);
source('.octaverc');
OUTFILE_SUFFIX = ".mat";

inFile = [INFILE_ROOT ticker INFILE_SUFFIX];
load(inFile);
labels = getBearishLabels(closes, interval, maxRatio);
sessionDates = sessionDates(1:end - interval);


outFile = [OUTFILE_ROOT pathTxt ticker OUTFILE_SUFFIX];
save("-mat-binary", outFile, "labels", "sessionDates");

end
