predictors/neural/03
===
3-layer neural network using 420 neurons and regularized data.

Mean of each row of features is adjusted to 0, and standard deviation is adjusted to 1.
This algorithm is exactly like neural/02 except for normalization of features.

Purpose
---
- See if feature normalization helps with an algorithm that is showing some
predictive power already.

Results
---
Random initialization 02 resulted in the highest precision.

### Scores

#### Test

##### Using learned parameters
- F1: 71.4% (70.4% for neural/02)
- precision: 56.8% (57.4% for neural/02)
- recall: 96.0% (91.0% for neural/02)

##### Baseline (constant prediction of 1)
- F1: 72.1%
- precision: 56.4%
- recall: 100.0%

#### Train

##### Using learned parameters
- F1: 73.8% (74.1% for neural/02)
- precision: 60.0% (60.4% for neural/02)
- recall: 95.8% (95.9% for neural/02)

##### Baseline (constant prediction of 1)
- F1: 74.2%
- precision: 58.9%
- recall: 100.0%

### Run time
- MacBook Pro 2.6 GHz Intel Core i7, 16 GB 1600 MHz DDR3: about 60 minutes

Conclusions
---
In comparison to neural/02, the results are unclear. On the test data,
normalization lead to a 1% higher f1 score, but we sacrificed 0.6% in precision, which
is the bottleneck.

### Next steps
#### Most promising
- use more parameters (volumes, S&P data)
- use continuous labels: upside as pct of downside or close at target as multiple of current.

#### Other
- regularization

Parameters
---
<table>
    <tr>
        <th>Parameter</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>nNeurons</td>
        <td>420</td>
    </tr>
    <tr>
        <td>maxIter</td>
        <td>64</td>
    </tr>
    <tr>
        <td>lambda</td>
        <td>0</td>
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
