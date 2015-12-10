data/sp500
===
Data sets from the S&P 500

Details
---
`constituents.csv` is a list of constituents as of
2015-11. Other files follow the pattern: 

- `train<nn>.csv` for 
a group of equities that has been selected randomly from the
index as training data
- `model<nn>.npz` for the model parameters
learned from training data
- `oos<nn>.csv` for a list of all S&P 500 equities
not in the training set (out-of-sample)

Building a model
---
To build a linear regression model used in 
visualizations:

    cd <PROJECT ROOT>/visualizers/linreg/common
    python
    >>> eqfile = '<PROJECT ROOT>/data/sp500/train<nn>.csv'
    >>> outfile = '<PROJECT ROOT>/data/sp500/model<nn>.npz'
    >>> equities = [line.strip() for line in open(eqfile)]
    >>> import save_model
    >>> save_model.run(equities, outfile)

