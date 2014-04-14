function [theta] = thetaFromSaved(ticker, featureType, featureInterval, labelType, labelInterval, labelVal)

% Return and save a theta value for logistic regression using a saved training set
% with the given parameters.
% 
% Usage example:
% theta = thetaFromSaved("combined", "splitadj-closes", 256, "bullish", 64, 4);
%
% Author: Marshall Farrier
% Since: 2014-04-14
% 

INPUT_ROOT_DIR = "./training-sets/";
OUTPUT_ROOT_DIR = "./theta/";
fileName = [featureType "/" sprintf("%d", featureInterval) "/" labelType "/"];
fileName = [fileName sprintf("%d/%dpct/", labelInterval, floor(labelVal * 100))];
fileName = [fileName ticker ".mat"];

load([INPUT_ROOT_DIR fileName]);
theta = getTheta(X, y);
save("-mat-binary", [OUTPUT_ROOT_DIR fileName], "theta");

end
