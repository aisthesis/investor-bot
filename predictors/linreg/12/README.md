predictors/linreg/12
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
-   Assess relevance of EMA 50.

Results
--
Cf. RESULTS.md

Conclusions
--
EMA 50 again seems to hurt slightly. For both EMA and SMA, this can
only be due to rounding errors as the matrix on which the inverse is
figured increases in size. I think the most interesting next step would be
to see whether decreasing the number of sessions (currently 256) makes.
That would immediately cut the number of features in half and reduce
inaccuracies due to floating point precision in inverting a large
matrix.

The following metrics clearly decreased the standard error:
-   EMA with span of 20
-   `ln(growth)`
-   Volatility with window of 20

Others are conceivably providing no information:
-   Simple growth
-   Volume
-   SMA with window of 20

Clearly no helpful information:
-   SMA with window of 50

Next Steps
--
Reduce the feature window from 256 to 128.

Incrementally try adding the following features:
-   EMA 50
-   Volatility 50

When finished adding, trying eliminating one at a time:
-   Growth
-   Relative volume
-   SMA

Features that don't seem to be helping shouldn't be used, as PCA
will pick them up, possibly to the detriment of the important
features.
