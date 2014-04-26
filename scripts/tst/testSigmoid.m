## Copyright (C) 2014 Marshall Farrier

## -*- texinfo -*-
## @deftypefn  {Function File} {} testSigmoid ()
## Unit tests for sigmoid function
## Usage:
## >> test("testSigmoid")
## @end deftypefn

## Author mdf
## Since 2014-04-25

function testSigmoid()
%!xtest "Size of matrix is preserved"
%! z = reshape(1:12, 4, 3);
%! assert(size(sigmoid(z)), size(z))
%!xtest "Always greater than 0"
%! assert(sigmoid(-10) > 0)
%! assert(sigmoid(0) > 0)
%! assert(sigmoid(10) > 0)
%!xtest "Always less than 1"
%! assert(sigmoid(-10) < 1)
%! assert(sigmoid(0) < 1)
%! assert(sigmoid(10) < 1)
%!xtest "Correct values"
%! assert(sigmoid(0), 0.5, 0.0001)
%! assert(sigmoid(-1) < 0.5)
%! assert(sigmoid(1) > 0.5)
end
