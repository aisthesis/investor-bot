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
It takes 192 components to get a reconstruction error of under 10 %.
However, that would translate to only 10 % of the data being noise,
and the financial data is clearly very noisy. Possibly as much as 50 %
is just noise. We drop below 50 % reconstruction error with only
15 components.

We should try PCA in multiples of 2 from 2 to 256 to see how the reduction
effects standard error for the various forecast intervals.

Next Steps
--
Apply linear regression on the compressed feature set, reducing dimension
to 2, 4, 8, 16, 32, 64, 128, 256
