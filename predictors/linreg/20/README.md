predictors/linreg/20
===
Description
--
Linear regression using extended features for
256 prior sessions as features and growth over varying prediction
intervals (same as `linreg/05`) as labels.

This is the canonical result for simple linear regression with
no regularization.

### Features

-   256 prior sessions
-   Centered and normalized
-   Content:
    -   Natural log of growth.
    -   SMA growth: 20 and 50
    -   EMA growth: 20 and 50
    -   Volatility of growth: 20

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
-   Use best set of features and restrict to relevant labels.

Results
--
Cf. RESULTS.md

Conclusions
--
As expected, the results improve slightly due to fewer rounding errors
with reduction of matrix size.

The following metrics clearly decreased the standard error:
-   EMA: 20, 50
-   `ln(growth)`
-   Volatility 20
-   SMA 20, 50

Irrelevant
-   Simple growth
-   Relative volume
-   Growth volatility 50

Next Steps
--
PCA. PCA is likely more useful at this point than regularization.
If we can get the features down to a manageable number without significant
information loss, we can then begin to test nonlinear transformations.

Features that don't seem to be helping shouldn't be used, as PCA
will pick them up, possibly to the detriment of the important
features.
