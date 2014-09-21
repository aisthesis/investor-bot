## Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
##
## Distribution and use of this software without prior written permission
## of the authors is strictly prohibitied and will be prosecuted to
## the full extent of the law.

## -*- texinfo -*-
## @deftypefn  {Function File} {} recommend (@var{recommenderFcn}, @var{predictorId}, @var{equitiesFile})
## Save recommendations for target equities as csv.
##
## The @var{recommenderFcn} passed will be used to transform the predictions vector
## produced by the specified predictor into a vector of recommendations.
##
## Use the equities and time periods from predictors/01 but
## always outputs 1 (buy) as baseline.
##
## Usage:
## 
## @example
## recommend(@@recsFromLabels, "logreg/01", "splitadj/closes/train60xval20test20/equities.csv");
## @end example
##
## @strong{Caution:} don't run this function directly but instead
## create a script documenting the parameters used and then calling this function.
## @end deftypefn

## Author: mdf
## Created: 2014-09-20

function recommend(recommenderFcn, predictorId, equitiesFile)

    PROJECT_ROOT = getenv("PROJECT_ROOT");
    PREDICTOR_DATA_ROOT = getenv("PREDICTOR_DATA_ROOT");
    equities = textread(sprintf(%s/%s", PREDICTOR_DATA_ROOT, equitiesFile));
    nEq = size(equities, 1);
    
    % get predictions for each equity and save
    ofile = "";
    HEADER = "Date,Strength";
    DOTTED_LINE_LIMIT = 64 * 64;
    createDir({"output"});
    for i = 1:nEq
        printfNow("Loading predictions for equity '%s'.\n", equities{i});
        % load prediction file for equity
        load(sprintf("%s/predictors/%s/output/%s.mat", PROJECT_ROOT, predictorId, equities{i}));
        % set strengths
        displayNow("Generating strengths.");
        strength = recommenderFcn(label);
        % save results
        printfNow("Saving strengths for equity %s", equities{i});
        nrows = size(strength, 1);
        ofile = sprintf("output/%s.csv", equities{i});
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
    endfor

endfunction
