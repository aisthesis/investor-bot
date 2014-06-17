function [closes] = getYahooCol(equity, col = 5)
% Extract a column vector from yahoo csv file for prices 
% and volume. If no column is specified, the close is
% returned as default.
%
% The data source is a csv file
% in the format produced by yahoo! finance and saved in 
% the data/ subdirectory.
%
% The function takes a string specifying the ticker
% of the equity and returns a column vector representing
% the given column of prices for the given time period. While the source data is
% stored in reverse chronological order, the vector returned
% will be in chronological order, starting with the oldest
% datapoint.
%
% Author: Marshall Farrier
% Since: 2014-04-10
% 

PATH_TO_DATA = getenv("DATA_ROOT");

% load the file 
all_data = csvread([PATH_TO_DATA equity ".csv"]);

% extract the column
closes = all_data(:, col);

% throw out the header row
closes = closes(2:end, :);

% reverse the order
closes = flipud(closes);
end
