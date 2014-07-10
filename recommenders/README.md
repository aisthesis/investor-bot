recommenders
===
Description
---
Recommenders process prediction results to arrive
at buy and sell recommendations.

Format
---
A recommender should have as output a set of `.csv` files
named by equity. The columns should be `Date` and `Strength`,
as reflected in a header row.

`Strength` is a real number between -1.0 and 1.0 where -1.0 is the
strongest possible sell recommendation and 1.0 is the strongest
possible buy recommendation.

The contents of a sample file `cat.csv` might be something like
this:

    Date,Strength
    2014-02-19,-0.314159
    2014-02-20,-0.1
    2014-02-21,0.0
    2014-02-24,1.0

There is no guarantee that ties between various stocks will be resolved
by different real number values: Some recommenders may simply specify
1.0 for buy, -1.0 for sell, and 0.0 for hold, or similar.

The rows should be sorted by date in chronological order (ascending).
