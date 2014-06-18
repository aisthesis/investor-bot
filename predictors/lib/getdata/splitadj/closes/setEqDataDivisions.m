## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{permutations} =} setEqDataDivisions ()
## Generates a random permutation of 1:3 for each equity in the
## file data/splitadj/closes/equities.csv and saves to
## a .mat file.
##
## Used for separating training, cross-validation and test
## data:
## 1 -> training
## 2 -> cross-validation
## 3 -> test
## @end deftypefn

## Author: mdf
## Created: 2014-06-17

function [permutations] = setEqDataDivisions()

PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
inFile = "equities.csv";
outFile = "eqDataDivisions.mat";

equities = textread([PREDICTOR_DATA_ROOT inFile], "%s");
permutations = struct("equity", {}, "permutation", {});
n = size(equities, 1);
for i = 1:n
    permutations(i).equity = equities{i};
    permutations(i).permutation = randperm(3);
endfor

save("-mat-binary", [PREDICTOR_DATA_ROOT outFile], "permutations");

end
