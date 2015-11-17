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
In this experiment, we used multiple random samples from the S&P, first
32 randomly selected equities for training and testing (`00`), then 64
for training and testing (`01`) and finally 128 for training and 64 for testing
(`02-04`).

With the larger selection, we could consistently improve on the baseline.
The larger training set also tends to reduce
overfitting and provides more thorough coverage. However, even with
a powerful laptop (16GB memory), processing the data took around 15 minutes
and required closing all other applications.

Build
---
Before running the visualization or validation code, you must
first build the model.
To build and save the learned model and preprocessing
parameters:

    cd common
    ./build
    
To reconstruct the error summaries:

    cd common
    python validate.py

Conclusions
---
Run on a random sample of the Dow, we saw that linear regression
actually does *worse* than the baseline out of sample. However, a fairly
large random selection (128 equities) from the S&P 500 allows the regression
algorithm to improve modestly but consistently over the baseline.

### Best
Through `sp500/model04` the most promising model is `sp500/model02`. The out
of sample error is slightly better than in the other models.

Next Steps
---
Using the model from one of the S&P 500 runs, visualize behavior on 
individual out-of-sample equities for which the model beats the baseline
as well as for the index itself.
