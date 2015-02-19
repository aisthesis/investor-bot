predictors/linreg/21
===
Description
--
Determine desirable cutoffs for PCA.

We have now found a set of features that provide
some information about future growth. In order to apply
nonlinear methods, we need to reduce these features using
PCA. The purpose of this trial is to look at the eigenvalues
found in single value decomposition to see what selections
look most promising.

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
1.  Get the eigenvalues for the svd of the non-constant features, of
    which we have 1792.
2.  Divide each eigenvalue by its successor. This gives a rate of
    forward decay. For example, if we have [10., 5., 4.] as eigenvalues,
    we would get [2., 1.25]. The bigger the number is, the more
    we will want to keep that eigenvalue.
3.  Setting a threshold of 1.05 (determined by prior experimentation),
    find candidate values for dimension reduction which isn't losing
    a lot of information.

### Notes
Svd for a matrix the size of our features matrix takes around 3 minutes
on my Mac, which has a 2.6 GHz Intel i7 and 16 GB of DDR3 memory.
Be patient when running this code.

Purpose
---
-   Find desirable parameters to use in PCA.

Results
--
### Indices of eigenvalues with decay > 1.05
    0,    1,    5,    6,
    7,    8,   10,   11,
    16,   18,   19,  24,
    271,  273,  275,  277,
    279,  282,  287,  290, 
    291,  321, 1530, 1531,
    1532, 1533, 1534, 1535,
    1536, 1784, 1786, 1787,
    1788, 1789, 1790

### Eigenvalues at the given locations
    
    2.44600856e+03   2.01158460e+03   1.71470941e+03   1.59312944e+03
    1.49028708e+03   1.24434748e+03   1.07122034e+03   9.98881821e+02
    8.20380777e+02   7.45999847e+02   6.89718333e+02   5.80941533e+02
    2.35913080e+02   2.12415979e+02   1.87038707e+02   1.63841538e+02
    1.42888494e+02   1.27170418e+02   1.11077295e+02   1.01152283e+02
    9.51299879e+01   5.31507824e+01   1.21680558e+00   9.86042893e-01
    6.52528716e-01   5.63440700e-01   4.56547579e-01   2.35028855e-01
    3.38407908e-13   1.68018061e-13   1.53701252e-14   9.01075619e-15
    7.74860119e-15   6.33784055e-15   3.62561954e-15

Conclusions
--
Reduce dimensions to 25 (index 24) or 322 (index 321).

Next Steps
--
Apply linear regression on the compressed feature set, reducing dimension
to 25.
