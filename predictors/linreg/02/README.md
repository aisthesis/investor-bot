predictors/linreg/02
===
Linear regression using split-adjusted closes normalized to a mean of 1
and volume data normalized to a mean of 1.

Labels will be a real number representing the relative value of the equity
64 sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

Purpose
---
- Determine whether the inclusion of volume allows linear regression
to improve out of sample over the simple baseline.

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
