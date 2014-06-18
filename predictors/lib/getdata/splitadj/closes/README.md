predictors/lib/getdata/splitadj/closes
===
Code for building datasets to be processed using
various prediction algorithms.

Scripts
---
- `build.m` is a generic script that should not be run
on its own because it will then create files with no way
to reconstruct the parameters used. Instead call this
function with a script like `build01.m`, which shows
exactly what parameters were used.
