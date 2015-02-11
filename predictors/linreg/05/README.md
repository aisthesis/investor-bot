predictors/linreg/05
===
Baseline linear regression using as a prediction the average
gain of all equities during the given time period. Just uses
a constant prediction factor.

Note that this prediction, simple as it is, is difficult to beat.
Linear regression using split-adjusted closes normalized to a mean of 1.

Labels will be a real number representing the relative value of the equity
some number of sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

Differences
--
In contrast to linreg/00, the baseline produced here tests
a variety of prediction intervals of size 2<sup>n</sup>: 1, 2, 4, 8, 16, 32, 64.
The results will then be compared with linear regression over
the same period.

Also, only the last 20 years (since 1995-01-01) of data is used. The 
adjusted close values further back are often so small that actual
daily returns get lost: With an adjusted close of .10, the minimum
daily gain or loss is 10%.

I'm also switching to standard error (sqrt of mean squared error rather
than raw mean squared error) because it provides a more accurate picture
of how much the model is normally off. This change amounts to using standard deviation
rather than variance. Standard deviation is more intuitive.

Purpose
---
- Establish a baseline standard for other algorithms.

Results
--
Cf. RESULTS.md
