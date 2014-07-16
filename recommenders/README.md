recommenders
===
Description
---
Recommenders process prediction results to arrive
at buy and sell recommendations.

Overview
---
### 00
Simplest viable recommender as baseline: Always recommend **buy** (1.0).

Output format
---
A recommender should have as output a set of `.csv` files
named by equity. The columns should be `Date` and `Strength`,
as reflected in a header row.

`Strength` is a real number between 0 and 1.0 where 0 is the
strongest possible sell recommendation and 1.0 is the strongest
possible buy recommendation.

Typically, 0 is to be interpreted as a **sell** recommendation,
0.5 as **hold** and 1.0 as **buy**. Relative strengths can be specified as real numbers
within the corresponding intervals [0, 0.333], [0.334, 0.666] and [0.667, 1].
Investors, however, are not obliged to follow these guidelines, but departures
are likely to be unwise except near the borders between the corresponding
intervals.

The contents of a sample file `cat.csv` might be something like
this:

    Date,Strength
    2014-02-19,0.314159
    2014-02-20,0.5
    2014-02-21,0.0
    2014-02-24,1.0

There is no guarantee that ties between various stocks will be resolved
by different real number values: Some recommenders may simply specify
1.0 for buy, 0 for sell, and 0.5 for hold, or similar.

The rows should be sorted by date in chronological order (ascending).
