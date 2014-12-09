predictors/linreg/01
===
Linear regression using split-adjusted closes normalized to a mean of 1.

Labels will be a real number representing the relative value of the equity
64 sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

Purpose
---
- Build a basic linear regression using Python.
- Given the results of logistic regression without volume data, it
is highly unlikely that the results will beat our baseline.

Results
--
Cf. RESULTS.md

Conclusions
--
Here, too, we see that without volume data (and using a linear model), we
are unable to improve on the baseline of taking average growth for the entire
data set.
