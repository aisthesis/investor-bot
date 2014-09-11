## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} ohlcMatToCsv ()
## Saves the matlab binary data stored in files @var{ticker}-splitadj.mat
## in csv files @var{ticker}-splitadj.csv
##
## Usage:
##
## @example
## ohlcMatToCsv()
## @end example
## @end deftypefn

## Author mdf
## Since 2014-09-10

function ohlcMatToCsv()

equities = {
    "cat",
    "dd",
    "f",
    "ge",
    "ibm",
    "jnj",
    "jpm",
    "xom"
};
nEq = size(equities, 1);

INFILE_SUFFIX = "-splitadj.mat";
OUTFILE_SUFFIX = "-splitadj.csv";
DATA_ROOT = getenv("DATA_ROOT");

HEADER = "Date,Open,High,Low,Close,Volume,Adj Close";
DOTTED_LINE_LIMIT = 64 * 64;

ofile = "";
nrows = 0;

for i = 1:nEq
    load(sprintf("%s%s%s", DATA_ROOT, equities{i}, INFILE_SUFFIX));
    nrows = size(closes, 1);
    ofile = sprintf("%s%s%s", DATA_ROOT, equities{i}, OUTFILE_SUFFIX);
    printfNow("Writing output for equity '%s'.\n", equities{i});
    fid = fopen(ofile, "w");
    fputs(fid, HEADER);
    printfNow(". ");
    for j = 1:nrows
        fprintf(fid, "\n%s,%6.4f,%6.4f,%6.4f,%6.4f,%d,%6.4f", datestr(sessionDates(j), "yyyy-mm-dd"), 
            opens(j), highs(j), lows(j), closes(j), volumes(j), adjCloses(j));
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
