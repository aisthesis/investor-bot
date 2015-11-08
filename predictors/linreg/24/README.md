predictors/linreg/24
===
Description
--
Linear regression using extended features for
256 prior sessions as features and growth over varying prediction
intervals as labels.

In linreg/20 we determined that prediction intervals < 32 don't allow
any improvement over the baseline. There is too much noise in the
short-term labels. But we only tested up to a prediction interval of
128. Here we test up to 512 for purposes of comparing to the corresponding
baselines.

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
   
### Labels
Growth for varying forecast intervals incremented in powers of 2.
Lowest forecast distance is 32, as we have already determined (cf. linreg/20)
that smaller intervals don't provide any greater accuracy than the baseline.

### Method
Linear regression with no regularization.

### Error metric
Standard error (sqrt of mean squared error).

### Notes
Only the last 20 years (since 1995-01-01) of data is used. The 
adjusted close values further back are often so small that actual
daily returns get lost: With an adjusted close of .10, the minimum
daily gain or loss is 10%.

Purpose
---
-   Determine most promising forecast distance.

Results
--
Cf. RESULTS.md

Conclusions
--
### Prior conclusions
The following metrics clearly decreased the standard error:
-   EMA: 20, 50
-   `ln(growth)`
-   Volatility 20
-   SMA 20, 50

Irrelevant
-   Simple growth
-   Relative volume
-   Growth volatility 50

PCA unfortunately doesn't seem to allow significant data compression.

Next Steps
--
