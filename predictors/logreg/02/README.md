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

Results
---
On test data:
- F1 score: 67.2% (71.3% in logreg/01)
- precision: 53.7% (55.6% in logreg/01)
- recall: 90.0% (99.6% in logreg/01)

Conclusions
---
Contrary to hypothesis,
it does look like there is enough overfitting to make it worthwhile
to use regularization.

I also noticed that there were some mistakes in logreg/01 in dividing
up test, xval and training sets: The variable startRow never gets reset in lines 68-83 
of https://github.com/aisthesis/investor-bot/blob/marshall/predictors/getdata/splitadj/closes/trainCvTestEquity.m.
The data sets  need to be properly separated in order to
have a valid frame of reference.

Parameters
---
<table>
    <tr>
        <th>Parameter</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>maxIter</td>
        <td>64</td>
    </tr>
    <tr>
        <td>labelType</td>
        <td>"bullish"</td>
    </tr>
    <tr>
        <td>labelMakerFcn</td>
        <td>"bullLabEquity"</td>
    </tr>
    <tr>
        <td>featureInterval</td>
        <td>256</td>
    </tr>
    <tr>
        <td>labelInterval</td>
        <td>64</td>
    </tr>
    <tr>
        <td>ratio</td>
        <td>1.0</td>
    </tr>
</table>
