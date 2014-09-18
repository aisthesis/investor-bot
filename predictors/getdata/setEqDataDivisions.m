## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{permutations} =} setEqDataDivisions (@var{path}, @var{nDivisions})
## If no permutation has been previously generated, a random permutation of 1:nDivisions for each equity in the
## file @var{path}/equities.csv is created and saved to a .csv file @var{path}/divisions-@var{nDivisions}.csv
##
## First, the function looks for a pre-existing .csv file. If it exists, then its data is taken as source
## for creation of a .mat file, which must first be built. Note that since a random permutation is used,
## it is normally not desirable to overwrite the permutation chosen, since it is used multiple times
## in the predictor pipeline.
##
## To create a new random permutation, simply run this funtion after deleting the .csv file generated
## on first run.
##
## The data in the .csv file is then used to create a .mat file of the same name, which contains a
## @var{permutations} struct for fast access in Octave.
##
## Can be used for separating training, cross-validation and test
## data:
## @itemize
## @item
## 1 -> training
## @item
## 2 -> cross-validation
## @item
## 3 -> test
## @end itemize
##
## Or for separating training and test data sets:
## @itemize
## @item
## 1 -> training
## @item
## 2 -> test
## @end itemize
##
## Usage:
##
## @example
## permutations = setEqDataDivisions("../train70-test30", 2)
## @end example
## @end deftypefn

## Author: mdf
## Created: 2014-09-17

function [permutations] = setEqDataDivisions(path, nDivisions)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% get permutations: from file if it exists, otherwise create file
PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
inFile = sprintf("%s/%s/equities.csv", PREDICTOR_DATA_ROOT, path);
outFile = sprintf("%s/%s/divisions-%d.csv", PREDICTOR_DATA_ROOT, path, nDivisions);

permutations = struct();

if exist(outFile, "file")
    % csv file exists
    inFile = outFile;
    displayNow("Random permutation csv exists. Reading from file.");
    line = "";
    fid = fopen(inFile, "r");
    while true
        line = fgetl(fid);
        if line == -1
            break;
        endif
        elems = strsplit(line, ",");
        permutations.(elems{1}) = [];
        for i = 1:nDivisions
            permutations.(elems{1})(i) = str2num(elems{i + 1});
        endfor
    endwhile
else
    % csv file doesn't exist, so create it
    displayNow("Generating random permutations.");
    equities = textread(inFile, "%s")
    nEquities = size(equities, 1)
    for i = 1:nEquities
        permutations.(equities{i}) = randperm(nDivisions);
    endfor
    displayNow("Writing permutations to csv file.");
    fid = fopen(outFile, "w");
    for i = 1:nEquities
        fprintf(fid, "%s%s", ifelse(i > 1, "\n", ""), equities{i});
        for j = 1:nDivisions
            fprintf(fid, ",%d", permutations.(equities{i})(j));
        endfor
    endfor
    fclose(fid);
    displayNow("Permutations written to csv.");
endif

% now save in binary format
displayNow("Saving result in matlab binary format.");
outFile = sprintf("%s/%s/divisions-%d.mat", PREDICTOR_DATA_ROOT, path, nDivisions);
save("-mat-binary", outFile, "permutations");
displayNow("Permutation saved.");

end
