predictors/linreg/02
===

Summary
--
Linear regression.

### Features

- daily returns on split-adjusted closes for 256 prior sessions
    1. center each column to mean 0
    2. normalize by column to SD of 1.0 (multiply each column by 1 / sigma)
- volume for 256 prior sessions
    1. express today's volume as multiple of average over prior 255 sessions
    for given equity. Note: 255 so as not to include currently day.
    2. featurize over 256 sessions
    3. center each  column to mean 0
    4. normalize by column to SD of 1.0

Centering and normalization vectors need to be saved, as they must be applied
to the test data set as is.

As long as (excluding constant feature) the first 256 features are always
returns and the next 256 are always volumes, the centering and 
normalization can be done after featurization so that there is one adjustment
vector to be used for testing.

Labels will be a real number representing the relative value of the equity
64 sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

Purpose
---
- Get features that can be used for PCA and for radial basis functions.
- Verify that the given features perform at least as well as those used
in linreg/02.

Next Steps
--
- Substitute ln of daily return for daily return (suggested in the literature).

[TODO: The following remarks are placeholders]
==
Results
--
Cf. RESULTS.md

Conclusions
--
While far from conclusive, the improvement in Ein over `linreg/01` suggests
that volume is providing useful information. Average Ein for current model:
0\.01890 vs. 0.01898 for `linreg/01` with a basline for Ein of 0.01916.
The differences are sufficiently small between all 3 that the improvement
in the current model appears noteworthy.

At the same time, Eout becomes negligibly *worse* in the current model,
suggestive of overfitting. It doesn't seem worth it to work on
regularization here, however, since we're really looking for more improvement
than even the in-sample error is providing.

Next Steps
--
Nonlinear functions are clearly needed in order to get adequate predictive
value. Possible approaches:

-   Radial basis functions
-   Nonlinear transformations. In order to make this work, we would clearly
    need to apply PCA for feature reduction, since with the introduction of
    volume, we're working with 513 features. If we could use PCA to reduce
    to around 16 features (sqrt(256)), we could then try the same method
    used here using a polynomial of all features of order 2.

    For easy implementation: 
    http://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.PolynomialFeatures.html

Nonlinear transformations are a little easier, but both techniques should be tried.
We may also need PCA to get acceptable runtimes for Radial basis functions.
