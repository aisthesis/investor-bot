function [X, y] = combineTrainingSets(featureType, featureInterval, labelType, labelInterval, labelVal)

% Using the given parameters combine and save pre-existing training sets for individual
% equities into a single, comprehensive training set.
%
% Author: Marshall Farrier
% Since: 2014-04-14
% 

% Get paths
pathToInput = ["./training-sets/" featureType "/" sprintf("%d", featureInterval) "/" labelType "/"];
pathToInput = [pathToInput sprintf("%d/%dpct/", labelInterval, floor(labelVal * 100))];
suffix = ".mat";
outputName = "combined";
outFile = [pathToInput outputName suffix];

% set up container variables
X_all = [];
y_all = [];

equities = { "cat", "dd", "f", "ge", "ibm", "jnj", "jpm", "xom" };
for i = 1:length(equities)
    load([pathToInput equities{i} suffix]);
    X_all = [X_all; X];
    y_all = [y_all; y];
endfor

X = X_all;
y = y_all;
save("-mat-binary", outFile, "X", "y");

end
