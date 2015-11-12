visualizers/linreg
===
Description
---
Assemble datasets based on linear regression that
will have the format appropriate for passing to
visualization tools.

Build
---
Before running the visualization or validation code, you must
first build the model.
To build and save the learned model and preprocessing
parameters:

    cd common
    ./build

Notes
---
Run on a random sample of the Dow, we see that linear regression
actually does *worse* than the baseline out of sample.

Next Steps
---
Run the algorithm on a random sample of the entire S&P 500, selecting
half for learning and half for testing.
