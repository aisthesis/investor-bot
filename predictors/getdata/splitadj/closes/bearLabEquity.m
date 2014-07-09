function [y] = bearLabEquity(ticker, interval, maxRatio)

% Given a ticker, an interval, and a maximum ratio, return and save
% labels for all available data.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

displayNow("bearLabEquity() called");
INFILE_ROOT = getenv("DATA_ROOT");
INFILE_SUFFIX = "-splitadj.mat";
OUTFILE_ROOT = getenv("PREDICTOR_DATA_ROOT");
path = {"labels" sprintf("%d", interval) "bearish" sprintf("%dpct", floor(maxRatio * 100))}; 
pathTxt = createDir(path, OUTFILE_ROOT);
OUTFILE_SUFFIX = ".mat";
outFile = sprintf("%s%s%s%s", OUTFILE_ROOT, pathTxt, ticker, OUTFILE_SUFFIX);

if exist(outFile)
    printfNow("Skipping file %s because it already exists.\nDelete file and rerun this function to rebuild it.\n\n", outFile);
    return;
endif

inFile = sprintf("%s%s%s", INFILE_ROOT, ticker, INFILE_SUFFIX);
load(inFile);
y = getBearishLabels(closes, interval, maxRatio);
currDate = sessionDates(1:end - interval);

save("-mat-binary", outFile, "y", "currDate");
printfNow("file %s created.\n", outFile);

end
