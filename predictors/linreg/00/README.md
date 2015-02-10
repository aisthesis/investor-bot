predictors/linreg/00
===
Baseline linear regression using as a prediction the average
gain of all equities during the given time period. Just uses
a constant prediction factor.

Note that this prediction, simple as it is, is difficult to beat.
Linear regression using split-adjusted closes normalized to a mean of 1.

Labels will be a real number representing the relative value of the equity
64 sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

Purpose
---
- Establish a baseline standard for other algorithms.

Results
--
Cf. RESULTS.md
