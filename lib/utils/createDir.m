## Copyright (C) 2014 Marshall Farrier

## -*- texinfo -*-
## @deftypefn  {Function File} {} createDir (@var{path}, @var{root})
## Create a directory.
## 
## Create a directory starting from the given root and using
## the sequence of subdirectories specified in path, which must be a cell array
## containing the names of each subdirectory in sequence.
## Example usage:
## createDir({"foo" "bar"}, "~")
## This will create the directory ~/foo/bar/ and then return to the
## directory from which createDir() was called.
##
## The function returns a status of 1 if the operation was successful. Otherwise,
## status is 0;
## @end deftypefn

## Author mdf
## Since 2014-04-25

function status = createDir(path, root = ".")
currentDir = pwd;
status = 0;
warning("off", "all", "local");
try
    cd(root);
    for i = 1:length(path)
        mkdir(path{i});
        cd(path{i});
    endfor
catch
    cd(currentDir);
    return
end_try_catch
cd(currentDir);
status = 1;
end
