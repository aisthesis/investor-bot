"""
Generate reports.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

def errors_by_dist(results, distances):
    """
    Error report showing dependency on forecast distance

    Parameters
    --
    results : list {metrics.EinEout}
        Results to report

    growth_aves : ndarray
        Row vector of showing average growth for each
        interval.

    distances : list {int}
        distances to use for report
    """
    contents = []
    contents.append( """\
Error Summary
==
<table>
<tr>
    <th>Metric</th>
    <th>Forecast Distance</th>
    <th>Ave.</th>
    <th>High</th>
    <th>Low</th>
</tr>
""")

    for i in range(len(results)):
        contents.append("""
<tr>
    <td>Eout</td>
    <td>{}</td>
    <td>{:6.4f}</td>
    <td>{:6.4f}</td>
    <td>{:6.4f}</td>
</tr>
<tr>
    <td>Ein</td>
    <td>{}</td>
    <td>{:6.4f}</td>
    <td>{:6.4f}</td>
    <td>{:6.4f}</td>
</tr>
""".format(distances[i], results[i].eout.average, results[i].eout.highest, results[i].eout.lowest,
            distances[i], results[i].ein.average, results[i].ein.highest, results[i].ein.lowest))

    contents.append("</table>")
    return ''.join(contents)

def growth_by_dist(growth_aves, distances):
    contents = []
    contents.append("""\
Growth
==
<table>
<tr>
    <th>Forecast Distance</th>
    <th>Ave. Growth</th>
</tr>
""")

    for i in range(growth_aves.shape[1]):
        contents.append("""
<tr>
    <td>{}</td>
    <td>{:6.4f}</td>
</tr>
""".format(distances[i], growth_aves[0, i]))

    contents.append("</table>")
    return ''.join(contents)
