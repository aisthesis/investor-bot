## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} csvOutput ()
## Save strengths (recommendations) for target equities in csv format.
##
## @itemize
## @item
## The file will include a header row with the titles
## @code{Date} and @code{Strength}
##
## @item
## The @code{Date} field will be in @code{yyyy-mm-dd} format,
## like @code{2014-07-10}
## @end itemize
## 
## Dependencies:
##
## @itemize
## @item
## @code{getRecommendations()} must be run prior to running this script.
## @end itemize
##
## Usage:
## 
## @example
## csvOutput()
## @end example
##
## @end deftypefn

## Author: mdf
## Created: 2014-07-15

function csvOutput()
    
    ROOT_PATH = "output";
    OUTFILE_SUFFIX = "csv";
    INFILE_SUFFIX = "mat";
    PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
    HEADER = "Date,Strength";
    DOTTED_LINE_LIMIT = 64 * 64;

    infile = "equities.csv";
    ofile = "";
    nrows = 0;

    % get equities list
    equities = textread(sprintf("%s%s", PREDICTOR_DATA_ROOT, infile), "%s");
    nEq = size(equities, 1);

    % load data and save in csv format
    for i = 1:nEq
        load(sprintf("%s/%s.%s", ROOT_PATH, equities{i}, INFILE_SUFFIX));
        nrows = size(strength, 1);
        ofile = sprintf("%s/%s.%s", ROOT_PATH, equities{i}, OUTFILE_SUFFIX);
        printfNow("Writing output for equity '%s'.\n", equities{i});
        fid = fopen(ofile, "w");
        fputs(fid, HEADER);
        printfNow(". ");
        for j = 1:nrows
            fprintf(fid, "\n%s,%d", datestr(currDate(j), "yyyy-mm-dd"), strength(j));
            if mod(j, 64) == 63
                if mod(j, DOTTED_LINE_LIMIT) == DOTTED_LINE_LIMIT - 1
                    displayNow("");
                endif
                printfNow(". ");
            endif
        endfor
        fclose(fid);
        displayNow("");
    endfor

endfunction
