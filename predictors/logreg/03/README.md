predictors/logreg/03
===
Logistic regression using split-adjusted closes.

Purpose
---
- To fix problems in data set separation in lines 68-83 of
https://github.com/aisthesis/investor-bot/blob/marshall/predictors/getdata/splitadj/closes/trainCvTestEquity.m.
- To set up a clean directory structure to allow maximal re-use of
data sets.

Placeholders (TODO)
===

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
