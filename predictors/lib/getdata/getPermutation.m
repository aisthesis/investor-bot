## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{permutation} =} getPermutation (@var{equity}, @var{permutations})
## Retrieve the permutation for the given equity given a struct array containing structures
## with a field equity and a field permutation.
## @end deftypefn

## Author mdf
## Since 2014-06-18

function permutation = getPermutation(equity, permutations)

permutation = [];
n = length(permutations);

for i = 1:n
    if strcmp(equity, permutations(i).equity)
        permutation = permutations(i).permutation;
        return;
    endif
endfor

end
