predictors/linreg/02
===

Summary
--
Linear regression.

### Features

- daily growth (today's value / yesterday's) on split-adjusted closes for 256 prior sessions
- volume for 256 prior sessions
    1. express today's volume as multiple of average over prior 251 sessions (1 year)
    for given equity. Note: 255 so as not to include currently day.
    2. featurize over 256 sessions

Labels will be a real number representing the relative value of the equity
64 sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

Purpose
---
- Get features that can be used for PCA and for radial basis functions.
- Verify that the given features perform at least as well as those used
in linreg/02 before centering and normalizing.

Results
--
Cf. RESULTS.md

Conclusions
--
The results are minimally better on both `eout` and `ein` than in linreg/02, so we're
at least not losing any ground. There appears to be some overfitting, but the
more significant issue is the model itself, since even `ein` isn't great. These
features will allow us to implement PCA after centering and normalization,
assuming that those operations aren't detrimental. Then we will be in a position
to start working with non-linear models.

Next Steps
--
- Center and normalize features
