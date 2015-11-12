"""
Generate formatted reports.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

def errorsbydistance(baseline_err, model_err, distances, model_name='Model'):
    contents = []
    contents.append("""\
Error Summary
==
<table>
<tr>
    <th>Metric</th>
    <th>Distance</th>
    <th>Std. Error</th>
</tr>
""")
    for i in range(len(distances)):
        contents.append("""
<tr>
    <td>{}</td>
    <td>{}</td>
    <td>{:6.4f}</td>
</tr>
<tr>
    <td>Baseline</td>
    <td>{}</td>
    <td>{:6.4f}</td>
</tr>
""".format(model_name, distances[i], model_err[i], distances[i], baseline_err[i]))

    contents.append('</table>')
    return ''.join(contents)
