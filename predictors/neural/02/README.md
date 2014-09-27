predictors/neural/02
===
3-layer neural network using 420 neurons.

Purpose
---
- See if increasing the number of neurons will improve predictive power.
- Determine run-times.

Results
---
Random initialization 02 resulted in the highest precision.

### Scores

#### Test

##### Using learned parameters
- F1: 70.4%
- precision: 57.4%
- recall: 91.0%

##### Baseline (constant prediction of 1)
- F1: 72.1%
- precision: 56.4%
- recall: 100.0%

#### Train

##### Using learned parameters
- F1: 74.1%
- precision: 60.4%
- recall: 95.9%

##### Baseline (constant prediction of 1)
- F1: 74.2%
- precision: 58.9%
- recall: 100.0%

### Run time
- MacBook Pro 2.6 GHz Intel Core i7, 16 GB 1600 MHz DDR3: about 60 minutes

Conclusions
---
420 neurons show a noticeable improvement in precision, albeit still only around
1.0% better than baseline on the test data. And recall also suffers a good deal for
the 1% increase in precision. It would be interesting to know whether the positives
we're missing (error in recall) are generally times when the stocks are staying
pretty neutral. We definitely don't want to be missing times when the stocks are 
experiencing growth spurts.

### Next steps
#### Most promising
- use more parameters (volumes, S&P data)
- normalize the data
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
