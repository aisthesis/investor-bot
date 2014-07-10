## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} getData ()
## Generate the data sets needed to run the current machine learning
## algorithm.
##
## Parameters are specified in the file 'params.mat'
##
## Usage:
##
## @example
## getData()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-09

function getData()
    load('params.mat');
    build(str2func(labelMakerFcn), featureInterval, labelInterval, ratio);

end
