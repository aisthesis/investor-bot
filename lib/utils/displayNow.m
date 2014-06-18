## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues

## -*- texinfo -*-
## @deftypefn  {Function File} {} displayNow (@var{msg})
## Display the given message immediately. The standard function
## disp() may wait too long while other threads are running.
## @end deftypefn

## Author mdf
## Since 2014-06-17

function displayNow(msg)

disp(msg);
if exist('OCTAVE_VERSION')
    fflush(stdout);
endif

end
