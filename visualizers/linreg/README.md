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
first create a model for generating predictions.

### Models
Building and saving *all* learned models and preprocessing
parameters will take some time. Expect at least an hour. To do so:

    cd common
    ./build

You will need all models if you want to reconstruct all error
summaries, but if you just want to do visualizations based on
a particular model, you only need to build one particular model.
For example, if you wanted to build and save the model for the selection
of equities listed in `./sp500/train02.csv`, you could run
the following code:

    cd common
    python
    >>> import save_model
    >>> import os
    >>> cwd = os.path.dirname(os.path.realpath(__file__))
    >>> path = os.path.normpath(os.path.join(cwd, '../sp500'))
    >>> eqfile = os.path.join(path, 'train02.csv')
    >>> equities = [line.strip() for line in open(eqfile)]
    >>> outfile = os.path.join(path, 'model02.npz')
    >>> save_model.run(equities, outfile)

If you create a completely new model (i.e., one using a selection of equities
not previously tested), it is strongly recommended to run the
validation code in `validate.py` before using it. Otherwise, you
may be visualizing a model that happens to work well on some equities
but which won't reliably generalize.
    
### Error summaries
To reconstruct *all* error summaries:

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
