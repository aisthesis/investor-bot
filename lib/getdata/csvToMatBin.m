function csvToMatBin(ticker)

% WARNING!!! This takes several minutes to run
% due to the date conversions. Expect the program to take about
% 5 minutes for each dataset on a fast, multi-core computer.
%
% Given a ticker symbol corresponding to a csv file
% provided by yahoo, convert the data to a set of
% vectors in Octave, then save the vectors in
% matlab binary format.
%
% Loading the resulting file will provide the following 
% variables as synchronized column vectors:
% - sessionDates
% - opens
% - highs
% - lows
% - closes
% - volumes
% - adjCloses
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

PATH_TO_DATA = getenv("DATA_ROOT");
suffix = ".mat";
fileName = [PATH_TO_DATA ticker suffix];

% the dates are the only tricky part
% They will be stored as datenums
lines = textread([PATH_TO_DATA ticker ".csv"], "%s");
dates = strtrunc(lines(3:end), 10);
len = length(dates);
sessionDates = zeros(len, 1);

% This part takes quite a while
for i = 1:len
    sessionDates(i) = datenum(dates{i});
endfor
sessionDates = flipud(sessionDates);

opens = getYahooCol(ticker, 2);
highs = getYahooCol(ticker, 3);
lows = getYahooCol(ticker, 4);
closes = getYahooCol(ticker, 5);
volumes = getYahooCol(ticker, 6);
adjCloses = getYahooCol(ticker, 7);
save("-mat-binary", fileName, "sessionDates", "opens", "highs", "lows", "closes", "volumes", "adjCloses");

end
