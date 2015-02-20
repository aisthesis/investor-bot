"""
Generate reports.

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.

by

Marshall Farrier, marshalldfarrier@gmail.com
"""

def make_tbl(header_cells, contents, fmt=None):
    """
    Generic function for making a table.

    Parameters
    --
    header_cells : list {str}
        A list of column headers for the table. The number of columns
        in the table is determined by the length of this list.

    contents : list {list}
        The rows of the table. Each element in the list
        corresponds to a row and must have as many elements as
        the `header_cells` list.

    fmt : list {str}, optional
        If present, must have the same number of values as
        `header_cells`. Each column of the table body will be
        formatted using theses values. For strings in the 
        body, simply use the empty string as format string.
        For example: `[':6.4f', '', ':d']`.

    Returns
    --
    out : str
        html string for a table with the given contents, beginning
        with the `<table>` opening tag and ending with the `</table>`
        closing tag.
    """
    _rows = []
    _cells = []
    _n_cols = len(header_cells)
    _rows.append("<table>\n<tr>")
    for _cell in header_cells:
        _cells.append("<th>{}</th>".format(_cell))
    _rows.append("\n".join(_cells))
    del _cells[:]
    _rows.append("</tr>")
    if fmt is None:
        fmt = [''] * _n_cols
    for _row in contents:
        _rows.append("<tr>")
        for i in range(_n_cols):
            _cells.append("<td>{{{}}}</td>".format(fmt[i]).format(_row[i]))
        _rows.append("\n".join(_cells))
        del _cells[:]
        _rows.append("</tr>")
    _rows.append("</table>")
    return "\n".join(_rows)

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
