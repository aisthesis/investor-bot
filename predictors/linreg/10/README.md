predictors/linreg/09
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
    -   EMA growth. Span of 20 sessions.
    -   Volatility of growth. Window of 20 sessions.
    -   Natural log of growth.

`ln` of growth is usually used instead of growth. On big moves,
this will exaggerate downswings and understate upswings.
   
Only data since 1995 is used, as adjusted volumes on older data get so
small as to create additional noise due to rounding.

### Labels
Growth for varying forecast intervals incremented in powers of 2.
Same as for `linreg/05`, which established the baseline.

### Method
Linear regression with no regularization.

### Notes
Only the last 20 years (since 1995-01-01) of data is used. The 
adjusted close values further back are often so small that actual
daily returns get lost: With an adjusted close of .10, the minimum
daily gain or loss is 10%.

I've switched to *standard error* (sqrt of mean squared error) as error measure rather
than raw mean squared error because standard error provides a more accurate picture
of how much the model is normally off. This change amounts to using 
the more intuitive metric of standard deviation
rather than variance.

Purpose
---
-   Determine whether using `ln(growth)` can improve forecast accuracy.

Results
--
Cf. RESULTS.md

Conclusions
--
`ln(growth)` also helps. At this point we are a full percentage point
better than the baseline for forecast interval of 64 and between 3 (eout)
and 5 (ein) percentage points better for forecast interval 128.

Next Steps
--
Incrementally try adding the following features:
-   SMA 50
-   EMA 50
-   Volatility 50
