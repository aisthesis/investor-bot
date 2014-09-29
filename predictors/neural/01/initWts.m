## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{v} =} initWts ()
## 
## Save choices for initial weights to be used for the neural network.
##
## Usage:
##
## @example
## alreadyExists = initWts ()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-09-24

function alreadyExists = initWts()

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% parameters
featureInterval = 256;
nNeurons = csvread("params/neurons.csv");
nOfiles = 3;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

alreadyExists = 1;
theta1file = "";
theta2file = "";

% don't rebuild if they already exist

for i = 1:nOfiles
    theta1file = sprintf("params/theta1init%02d.csv", i);
    theta2file = sprintf("params/theta2init%02d.csv", i);
    alreadyExists = alreadyExists && exist(theta1file, "file") && exist(theta2file, "file");
endfor

if alreadyExists
    displayNow("Initialization files for theta1 and theta2 already exist. Delete to rebuild.");
    return;
endif

createDir({"params"});
for i = 1:nOfiles
    theta1file = sprintf("params/theta1init%02d.csv", i);
    theta2file = sprintf("params/theta2init%02d.csv", i);
    theta1init = randInitializeWeights(featureInterval, nNeurons);
    theta2init = randInitializeWeights(nNeurons, 1);
    if !exist(theta1file)
        csvwrite(theta1file, theta1init);
    endif
    if !exist(theta2file)
        csvwrite(theta2file, theta2init);
    endif
endfor

endfunction
