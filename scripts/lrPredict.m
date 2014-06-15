## Copyright (C) 2014 Marshall Farrier

## -*- texinfo -*-
## @deftypefn  {Function File} {} createDir (@var{path}, @var{root})
## Return a prediction vector having the value 1 in each position
## i where the i-th row of X times the vector theta is great
## than or equal to the given threshold.
## @end deftypefn

## Author mdf
## Since 2014-04-11

function [predictions] = lrPredict(X, theta, threshold = 0.5)

predictions = (sigmoid(X * theta) >= threshold);

end
