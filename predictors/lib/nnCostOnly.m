## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{j} =} nnCostOnly (@var{nnParams}, @var{nFeatures},
## @var{nNeurons}, @var{nLabels}, @var{X}, @var{y})
##
## Return the cost without regularization of gradient of the given @var{Params} over features X
## with respect to labels y
##
## Usage:
##
## @example
## j = nnCostOnly(nnParams, 256, 12, 1, X, y)
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-26
function [j] = nnCostOnly(nnParams, nFeatures, nNeurons, nLabels, X, y)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nnParams, nNeurons, nLabels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nnParams and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nnParams back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nnParams(1:nNeurons * (nFeatures + 1)), ...
                 nNeurons, (nFeatures + 1));

Theta2 = reshape(nnParams((1 + (nNeurons * (nFeatures + 1))):end), ...
                 nLabels, (nNeurons + 1));

m = size(X, 1);
j = 0;

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Part 1: Cost function

% Recode labels as row vectors
labels = zeros(m, nLabels);
for i = 1:nLabels
    labels(:, i) = (y == i);
endfor

% Add constant parameter to X
X = [ones(m, 1) X];

% Construct hidden layer
hiddenLayer = sigmoid(X * Theta1');
hiddenLayer = [ones(m, 1) hiddenLayer];

% Construct hypotheses
hypotheses = sigmoid(hiddenLayer * Theta2');

% Get cost
j = (1 / m) * sum(sum((-labels .* log(hypotheses)) - ((1 - labels) .* log(1 - hypotheses))));

end
