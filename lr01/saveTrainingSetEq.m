function saveTrainingSetEq(X, y, ticker, featureType, labelType, labelInterval, labelVal)

% Given feature sets X (including constant feature), labels y, ticker,
% featureType (such as "splitadj-closes"), labelInterval(such as 64),
% labelType ("bullish", "bearish" or "upside-exceeded"), and labelVal
% (4, 1, 0.25 for the value used in generating the labels), save the
% training set to an appropriately named matlab binary file.
%
% The feature interval is deduced from the dimensions of the X matrix
% and doesn't need to be passed as parameter.
%
% Author: Marshall Farrier
% Since: 2014-04-14
% 

savePath = ["./training-sets/" featureType "/" sprintf("%d", size(X, 2) - 1) "/" labelType "/"];
savePath = [savePath sprintf("%d/%dpct/", labelInterval, floor(labelVal * 100))];
suffix = ".mat";
outFile = [savePath ticker suffix];

save("-mat-binary", outFile, "X", "y");

end
