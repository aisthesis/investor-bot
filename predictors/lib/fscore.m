## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} fscore (@var{predicted}, @var{actual})
## @deftypefn  {Function File} {@var{v} =} fscore (@var{predicted}, @var{actual}, @var{beta})
## Return a vector containing the F score, precision and recall for predicted vs.
## actual values. @var{beta} defaults to 1, so if it is omitted, the resulting
## F score will be F1.
##
## Details:
## @uref{http://en.wikipedia.org/wiki/F1_Score}
##
## @var{predicted} and @var{actual} should be matrices of the same
## dimensions. The score, precision and recall will be returned
## for each column.
##
## @var{predicted} and @var{actual} are assumed to be matrices containing
## only 0 and 1 values.
##
## If provided, @var{beta} is a scalar which determines the relative weighting
## of precision vs. recall. A high (> 1) value of @var{beta} (frequent is 2) weights recall
## higher than precision, whereas a low (< 1) value for @var{beta} (such as 0.5)
## emphasizes precision more than recall. The default value of 1 represents
## equal weighting.
##
## Example usage:
##
## [score, precision, recall] = fscore(predicted, actual)
##
## [score, precision, recall] = fscore(predicted, actual, 0.5)
## @end deftypefn

## Author: mdf
## Created: 2014-06-20

function [score, precision, recall] = fscore(predicted, actual, beta = 1)
nActualPositives = sum(actual, 1);
nPredictedPositives = sum(predicted, 1);
nTruePositives = sum(predicted & actual, 1);

precision = nTruePositives ./ nPredictedPositives;
recall = nTruePositives ./nActualPositives;
score = (1 + beta ^ 2) * (precision .* recall) ./ (beta ^ 2 * precision + recall);

end
