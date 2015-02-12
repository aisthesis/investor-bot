predictors/linreg/06
===
Description
--
Linear regression using adjusted closes and volumes for
256 prior sessions as features and growth over varying prediction
intervals (same as `linreg/05`) as labels.

### Features
Growth of Adj Close and volume relative to recent average (past 252 sessions).
Each column is centered to mean 0 and normalized to std. dev. of 1. A constant
feature of 1. is also prepended.

Only data since 1995 is used, as adjusted volumes on older data get so
small as to create additional noise due to rounding.

### Labels
Growth for varying forecast intervals incremented in powers of 2.
Same as for `linreg/05`, which established the baseline

### Method
Linear regression with no regularization.

### Notes
In contrast to linreg/00, the baseline produced here tests
a variety of prediction intervals of size 2<sup>n</sup>: 1, 2, 4, 8, 16, 32, 64.
The results will then be compared with linear regression over
the same period.

Only the last 20 years (since 1995-01-01) of data is used. The 
adjusted close values further back are often so small that actual
daily returns get lost: With an adjusted close of .10, the minimum
daily gain or loss is 10%.

I'm switching to *standard error* (sqrt of mean squared error rather
than raw mean squared error) because it provides a more accurate picture
of how much the model is normally off. This change amounts to using standard deviation
rather than variance. Standard deviation is more intuitive.

Purpose
---
-   Determine if there is a sweet spot for the prediction interval, where
    we can see linear regression significantly outperforming the baseline
    esablished in `linreg/05`.

Results
--
Cf. RESULTS.md

Conclusions
--
There is no sweet spot using simple linear regression, even for more
short-term predictions

Next Steps
--
-   Add moving averages as features:
    -   SMA
    -   EMA
-   If moving averages help, see what happens if you remove actual
    closes altogether. There may be so much noise in actual prices
    that they provide no useful information at all.
-   If moving averages help, experiment with different parameters:
    20 day, 50 day, etc. Combinations are also possible.
