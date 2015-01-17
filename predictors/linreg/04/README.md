predictors/linreg/02
===

Summary
--
Linear regression.

### Features

- daily growth (today's value / yesterday's) on split-adjusted closes for 256 prior sessions
    1. center each column to mean 0
    2. normalize by column to SD of 1.0 (multiply each column by 1 / sigma)
- volume for 256 prior sessions
    1. express today's volume as multiple of average over prior 251 sessions
    for given equity (prior year). 
    2. featurize over 256 sessions
    3. center each  column to mean 0
    4. normalize by column to SD of 1.0

Labels will be a real number representing the relative value of the equity
64 sessions from the current date. For example, if the equity closes
today at 100.0 and 64 sessions later closes at 111.0, the label will be
1\.11 = 111.0 / 100.0

#### Preprocessing

Centering and normalization should occur only after the complete data set
hass been assembled and xval data has
been removed. The constant feature should of course be excluded from normalization
and centering. The transformations must also be saved so that they
can be applied as is to the test data.

Purpose
---
- Get features that can be used for PCA and for radial basis functions.
- Verify that the given features perform at least as well as those used
in linreg/03.

Results
--
Cf. RESULTS.md

Conclusions
--
The results are essentially identical to those in linreg/03 (average `Eout`
differs only after the 14th decimal place). So, centering and normalization
are not suppressing any relevant information.

Next Steps
--
- Use PCA to reduce features.
- Apply `ln()` to daily return (not growth!) before centering (suggested in the literature)?
