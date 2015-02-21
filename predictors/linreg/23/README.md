predictors/linreg/23
===
Description
--
Assess PCA with various numbers of components. We want
to determine how many components are needed to closely
match the results achieved in linreg/20, using all 
relevant features.

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

### Method
1.  For each division into training and cross-validation data,
    implement PCA to reduce the number of features in powers of
    2 from 2 to 256.
2.  Run linear regression as in linreg/20 to determine eout for
    each forecast interval using each level of compression.

### Notes
Svd for a matrix the size of our features matrix takes around 3 minutes
on my Mac, which has a 2.6 GHz Intel i7 and 16 GB of DDR3 memory.
Be patient when running this code.

Purpose
---
-   Find how much compression can be used to still get accurate
    predictions.

Results
--
Cf. `RESULTS.md`

Conclusions
--
The results are quite disappointing. Even with a reduction to
a 256 components, where we should have a reconstruction error
around only 2.6 %, we're not getting at all close to the results
achieved in `linreg/20` with the full set of features. Only at a compression
to 512 or 1024 do we get adequately accurate results.

Next Steps
--
-   Apply the same algorithms to the averages only (as represented by 'SPY').
    This would allow:
    -   Representing stocks relative to the average.
    -   Entering and exiting from a market portfolio as investment strategy.
