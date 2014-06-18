## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues

## -*- texinfo -*-
## @deftypefn  {Function File} {} printfNow (...)
## Same as printf() except that the message is displayed immediately
## rather than waiting for other threads to finish.
## @end deftypefn

## Author mdf
## Since 2014-06-17

function printfNow(varargin)

printf(varargin{:});
if exist('OCTAVE_VERSION')
    fflush(stdout);
endif

end
