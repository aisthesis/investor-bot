predictors/linreg/14
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
    -   Natural log of growth.
    -   Relative volume. Measured against average of last 252 sessions.
    -   SMA growth: 20 sessions (50 appears irrelevant)
    -   EMA growth: 20 and 50 sessions.
    -   Volatility of growth. Window of 20 sessions.

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
-   Redo linreg/10 (best run so far) to include 256 as forecast interval.

Results
--
Cf. RESULTS.md

Conclusions
--
The larger size of the labels matrix is also leading to some rounding
errors, so everything is slightly worse than in linreg/10. This should provide
an accurate starting point for eliminating irrelevant features.

Re-evaluating reduction of the session window (linreg/13), the additional
features seem almost irrelevant for shorter forecase windows (up to 16),
where eout is better but ein is worse using the reduced window. This result
suggests that the extra data is just causing overfitting for short-term
forecasts. For long-term forecasts, however, the extra data leads
to improvements of *both* ein *and* eout.

Re-evaluating EMA 50 (linreg/12), the results are largely identical. So EMA 50 doesn't
add anything.

Re-evaluating SMA 50 (linreg/11), we actually do get a little improvement.
SMA 50 should go back in before eliminating metrics.

The following metrics clearly decreased the standard error:
-   EMA with span of 20
-   `ln(growth)`
-   Volatility with window of 20
-   SMA 50 (marginally)

Others are conceivably providing no information:
-   Simple growth
-   Volume
-   SMA with window of 20

Next Steps
--
Try eliminating one at a time:
-   Growth
-   Relative volume
-   SMA

Incrementally try adding the following features:
-   EMA 50
-   Volatility 50

Features that don't seem to be helping shouldn't be used, as PCA
will pick them up, possibly to the detriment of the important
features.
