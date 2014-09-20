predictors/logreg/04
===
Logistic regression using **normalized** split-adjusted closes.

Features will be normalized so that each row has mean 0 and s.d 0.5.
Otherwise, all parameters will be as in logreg/03

Purpose
---
- To determine whether data normalization can improve predictive power.

TODO (Placeholder)
===

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


Conclusions
---
Regularization clearly improves results in this kind of logistic
regression.

Also, while increased iterations actually reduces overall F1 score,
the continuation leads to improved precision, which is our main
problem. I also tried 1024 iterations, but 512 seems to be the sweet
spot for maximizing precision.

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
