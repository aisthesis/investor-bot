visualizers/linreg
===
Description
---
Assemble datasets based on linear regression that
will have the format appropriate for passing to
visualization tools.

The learning and training data here are built differently
than they were for getting a baseline (`predictors/linreg/baseline00`)
and features on which linear regression could provide
better predictions (`predictors/linreg/24`). There, we were trying
to determine optimal features for making predictions
as accurate as possible. Here, we are trying to visualize
these predictions for purposes of seeing how we might
use them for building an investment strategy. For the present purpose,
we need to select the training and test data differently
than we did when exploring how to construct our predictor.

### Dow
In this experiment, we used a random selection from each sector represented
in the Dow as training data. Using the remaining Dow components
as test data, we can then verify that our algorithm achieves
results similar to those documented in `predictors/linreg/`.

### S&P 500

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
