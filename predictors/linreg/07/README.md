predictors/linreg/06
===
Description
--
Linear regression using extended features for
256 prior sessions as features and growth over varying prediction
intervals (same as `linreg/05`) as labels.

### Features

-   256 prior sessions
-   Centered and normalized
-   Content:
    -   Growth
    -   Relative volume. Measured against average of last 252 sessions.
    -   SMA growth. Last 20 sessions.
   
Note that raw SMA would lead to incomparable data points whenever
2 equities differ in value. So growth of SMA is used.

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
-   Determine relevance of SMA

Results
--
Cf. RESULTS.md

Conclusions
--
While adding SMA20 leads to a noticeable decrease in ein, the additional
feature also results in similarly increased eout. The additional
feature is causing some overfitting. This problem is likely
to increase with the addition of even more features. So, at
the end we will definitely need to regularize.

Next Steps
--
Incrementally try adding the following features:
-   log of growth
-   SMA 50
-   EMA 20 and 50
-   Volatility 20 and 50
