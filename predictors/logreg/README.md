predictors/logreg
===
Predictors using logistic regression.

Overview
---
### 01
#### Objective
Predict whether upside is at least 100 pct of downside
for the following 64 sessions.
#### Algorithm
- Uses logistic regression and no preprocessing other than
adjusting for splits. 
- Only closes of the individual equity are considered.
- 256 prior sessions are considered.
- An optimal regularization parameter is selected
by finding the best F1 score on the cross-validation set.
- Data is separated into training set, cross-validation set,
and test set in the proportion 60-20-20. Random blocks from each 
equity are used for extracting these sets.

#### Results
- The regularization parameter makes almost no difference running
the algorithm with 64 iterations (on the order of 0.1 pct).
- Recall is great (over 98 pct) but precision is low (around 55 pct):
The algorithm is almost always producing a positive.

#### Conclusions
- Try preprocessing the data to see if precision improves. Possibly
normalize each row so that the average over 256 sessions is 1.0


Company selection
---
While it will be important in the long run to include
a good selection of companies that have done poorly over
the timeframe available, this first attempts concentrate
on very conservative companies that have on the whole
succeeded over our timeframe. High-flyers such as MSFT or WMT
and disasters such as AIG have been excluded. The grouping
here is very solid companies with very low risk of going
under and good promise based on fundamentals (known independently
of data provided to the algorithm).
