predictors/logreg/04
===
Logistic regression using *normalized* split-adjusted closes.

Features will be normalized so that each row has mean 0 and s.d. 1.
Otherwise, all parameters will be as in logreg/03

Purpose
---
- To determine whether data normalization can improve predictive power.

Results
---
### On test data using 512 iterations:
- F1 score: 71.8% (68.4% in logreg/03)
- precision: 56.4% (57.7% in logreg/03)
- recall: 98.7% (84.0% in logreg/03)

Conclusions
---
Normalization improved F1 score by 3%, but at the cost of lower precision.
The results actually resemble those in logreg/03 using only 64 iterations.

Noteworthy is that the optimal lambda here was very small. Even 0 works pretty well.
So, the normalization seems to help prevent overfitting.

Next Steps
---
Try normalization only with the mean without adjusting standard deviation.

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
        <td>0.02</td>
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
