## Copyright (C) 2014 Marshall Farrier

## -*- texinfo -*-
## @deftypefn  {Function File} {@var{pathTxt}=} createDir (@var{path}, @var{root})
## Create a directory. Return a string that concatenates the elements of path,
## separating the components with '/'
## 
## Create a directory starting from the given root and using
## the sequence of subdirectories specified in path, which must be a cell array
## containing the names of each subdirectory in sequence.
## Example usage:
## pathTxt = createDir({"foo" "bar"}, "~")
## This will create the directory ~/foo/bar/ and then return to the
## directory from which createDir() was called. The function will
## return the string "foo/bar/"
##
## The function returns a status of 1 if the operation was successful. Otherwise,
## status is 0;
## @end deftypefn

## Author mdf
## Since 2014-04-25

function pathTxt = createDir(path, root = ".")
currentDir = pwd;
pathTxt = "";
warning("off", "all", "local");
try
    cd(root);
    for i = 1:length(path)
        mkdir(path{i});
        pathTxt = [pathTxt path{i} '/'];
        cd(path{i});
    endfor
catch
    cd(currentDir);
    return
end_try_catch
cd(currentDir);
end
