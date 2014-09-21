predictors/logreg/05
===
Logistic regression using split-adjusted closes normalized only to a mean of 0.

Features will be normalized so that each row has mean 0. In contrast to
logreg/04, standard deviation is not normalized.
Otherwise, all parameters will be as in logreg/04

Purpose
---
- To determine whether normalization by standard deviation is desirable.

Results
---
### On test data using 512 iterations:
- F1 score: 70.7% (71.8% in logreg/04)
- precision: 56.8% (56.4% in logreg/04)
- recall: 93.6% (98.7% in logreg/04)

Conclusions
---
Normalization by standard deviation improved F1 score but hurt precision.

This algorithm performed best with a high lambda of 512, but the difference
in scores on the *cross-validation* set was minimal for dramatically different
lambdas:
- 71.3% for lambda = 0
- 71.3% for lambda = 0.01
- 71.3% for lambda = 6.4
- 71.3% for lambda = 64.0
- 71.3% for lambda = 512
- 71.3% for lambda = 8192

Next Steps
---
### Logistic Regression
Develop recommendations using:
- logreg/03 (highest precision)
- logreg/04 (highest F1 score)

See how these perform in simulations.

### Linear Regression
Try developing a strength score expressing pct gain at some target date,
such as 128 sessions out.

Parameters
---
<table>
    <tr>
        <th>Parameter</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>maxIter</td>
        <td>512</td>
    </tr>
    <tr>
        <td>lambda</td>
        <td>512</td>
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
