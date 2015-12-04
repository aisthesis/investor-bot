predictors/linreg/store
===
Code for storing linear regression results to be used
in backtesting.

Requirements
===
Python
---
Use `requirements.txt` to install the necessary packages
in your virtual environment:

    mkvirtualenv invbot
    workon invbot
    pip install -r requirements.txt

MongoDB
---
You should create a unique index on the combination
of date and equity to prevent inconsistent data.
For example, from the `mongo` shell:

    > use invbot01
    switched to db invbot01
    > db.lrpred.createIndex({"Equity": 1, "Year": 1, "Month": 1, "Day": 1}, {unique: true})
    {
        "createdCollectionAutomatically" : true,
        "numIndexesBefore" : 1,
        "numIndexesAfter" : 2,
        "ok" : 1
    }
    >
