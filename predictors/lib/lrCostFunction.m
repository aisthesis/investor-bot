function [J, grad] = lrCostFunction(theta, X, y, lambda = 0)
%LRCOSTFUNCTION Compute cost and gradient for logistic regression with 
%regularization
%   J = LRCOSTFUNCTION(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 
% From homework in Coursera Machine Learning class

% Initialize some useful values
m = length(y); % number of training examples

% Initialize values to be returned
J = 0;
grad = zeros(size(theta));

reg = theta(2:end);
J = -(y' * (log(sigmoid(X * theta))) + ((1 - y') * log(1 - sigmoid(X * theta))));
J = J + (lambda / 2) * (reg' * reg);
J = (1 / m) * J;

reg = [0; lambda * reg];
grad = (1 / m) * (sum((sigmoid(X * theta) - y)' * X, 1)' + reg);
grad = grad(:);

end
