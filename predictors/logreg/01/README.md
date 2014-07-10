predictors/logreg/01
===
Logistic regression using split-adjusted closes

Results
---
F1 score on test data is 71.3%

Noteworthy is that recall is high (99.6%) whereas
precision is low (55.6%). So, we are catching almost everything
but have a lot of false positives.

Possible fixes:

- SVMs or neural networks
- Adding order 2 features (reducing to 128 or even 64 prior sessions to keep runtime
bearable.

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
