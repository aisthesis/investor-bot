predictors/neural/01
===
3-layer neural network using 60 neurons.

Purpose
---
- See if a neural network can increase precision over the baseline level.
- Determine run-times.

Results
---
Random initialization 02 resulted in the highest precision, which was
still hardly distinguishable from the baseline.

### Scores

#### Test

##### Using learned parameters
- F1: 72.2%
- precision: 56.5%
- recall: 99.9%

##### Baseline (constant prediction of 1)
- F1: 72.1%
- precision: 56.4%
- recall: 100.0%

#### Train

##### Using learned parameters
- F1: 74.2%
- precision: 59.0%
- recall: 99.8%

##### Baseline (constant prediction of 1)
- F1: 74.2%
- precision: 58.9%
- recall: 100.0%

### Run time
- MacBook Pro 2.6 GHz Intel Core i7, 16 GB 1600 MHz DDR3: about 30 minutes

Conclusions
---
60 neurons improves over logistic regression but is only improving precision
by 0.1% over the baseline. It is unlikely that we'd get significant improvement
by more iterations, as the cost is only decreasing by around 0.00002 per iteration
when we stop. The progression of cost is also now saved in the file "output/learned{00}.mat".

### Next steps
#### Most promising
- increase the number of neurons and/or add another layer
- use more parameters (volumes, S&P data)
- normalize the data

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
        <td>60</td>
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
