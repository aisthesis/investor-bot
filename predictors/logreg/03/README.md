predictors/logreg/03
===
Logistic regression using split-adjusted closes.

Purpose
---
- To fix problems in data set separation in lines 68-83 of
https://github.com/aisthesis/investor-bot/blob/marshall/predictors/getdata/splitadj/closes/trainCvTestEquity.m.
- To set up a clean directory structure to allow maximal re-use of
data sets.

Results
---
### On test data using 512 iterations:
- F1 score: 68.4% (67.2% in logreg/02)
- precision: 57.7% (53.7% in logreg/02)
- recall: 84.0% (90.0% in logreg/02)

### On test data using 64 iterations:
- F1 score: 71.6% (67.2% in logreg/02)
- precision: 56.4% (53.7% in logreg/02)
- recall: 97.8% (90.0% in logreg/02)

## Baseline
The baseline is just a constant prediction of 1 everywhere. So, precision
gives the percentage of 1s in the data set. Recall will always be 100%.
- F1 score: 72.1%
- precision: 56.4%
- recall: 100%

Conclusions
---
Regularization clearly improves results in this kind of logistic
regression.

Also, while increased iterations actually reduces overall F1 score,
the continuation leads to improved precision, which is our main
problem. I also tried 1024 iterations, but 512 seems to be the sweet
spot for maximizing precision.

Looking at the baseline, one can really only conclude that logistic
regression is inadequate as a predictor: We have only reached an improvement
of 1% in precision at the cost of a significant loss in recall and F1 score.
None of the attempts up to now have been able to beat the baseline in
any significant way.

Parameters
---
<table>
    <tr>
        <th>Parameter</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>maxIter</td>
        <td>512 / 64</td>
    </tr>
    <tr>
        <td>lambda</td>
        <td>0.1 / 1.6</td>
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
