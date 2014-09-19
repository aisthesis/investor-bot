predictors/logreg/02
===
Logistic regression using split-adjusted closes.

Purpose
---
The purpose of this trial is to determine whether searching
for an optimal regularization parameter is worthwhile.

The only difference between this attempt and logreg/01 is that no
regularization parameter is used here. It appears that simply setting
the regularization parameter (lambda) to 0 has negligible effect
on the accuracy of the predictions, but searching for it causes
much longer run-times, which are bearable for logistic regression
but will become very tedious with more sophisticated learning
algorithms. Eliminating the cross-validation data also means that
we have a larger training set, although it is also doubtful in this
case that increasing the size of the data set will improve predictive
power.
