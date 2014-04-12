function [predictions] = lrPredict(X, theta)

% Given a matrix X whose rows are features (including
% the constant feature) and a vector theta resulting from 
% logistic regression, return a vector of predictions for
% each row in X.
%
% Author: Marshall Farrier
% Since: 2014-04-11
% 

predictions = round(sigmoid(X * theta));

end
