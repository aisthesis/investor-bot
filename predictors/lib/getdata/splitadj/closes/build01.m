## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} build01 ()
## Calls build(256, 64, 4.0, 1.25, 1.0), i.e., using the parameters
## featureInterval: 256
## labelInterval: 64
## bullMinRatio: 4.0
## upsideMinRatio: 1.25
## bearMaxRatio: 1.0
## @end deftypefn

## Author: mdf
## Created: 2014-06-17

function build01()
build(256, 64, 4.0, 1.25, 1.0);
end
