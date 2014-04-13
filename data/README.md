Reusable source data
===
Files types:
---
- <code>&lt;ticker&gt;.csv</code>

    Comma-separated source data pulled from yahoo. The file has a header line and is
    sorted in reverse chronological order.

- <code>&lt;ticker&gt;.mat</code>

    Same data as <code>.csv</code> file but stored in binary matlab format and sorted
    chronologically. Loading the file creates 7 synchronized column vectors:

    - sessionDates (formatted as Octave/Matlab datenum)
    - opens
    - highs
    - lows
    - closes
    - volumes
    - adjCloses

    Note that this data has not been adjusted for splits unless yahoo has already made this
    adjustment (as in the adjusted close column, which also adjusts for dividends).

- <code>&lt;&gt;.png</code>

    Informational files, such as information on split dates. This data was consistent with
    price behavior except in the case of JPM, where the splits corresponded to those
    shown in the yahoo! chart but not to the splits shown on http://www.stocksplithistory.com/

- <code>&lt;ticker&gt;-splitadj.mat</code>

    Chronologically sorted matlab binary files adjusted to account for splits. These files are based on the data
    from <code>&lt;ticker&gt;.mat</code> and differ from them only in that they are adjusted for splits.

- <code>&lt;ticker&gt;-splitadjcloses.mat</code>

    matlab binary files with chronologically sorted closes that have been adjusted to account
    for splits by dividing prior values by the split factor. In other words, if the value sequence unadjusted is 
    something like 100.00, 101.00, 49.50, 51.05 before a 2:1 split, then all values up to and including
    the 101.00 would be divided by 2, so that the adjusted sequence would be 50.00, 50.50, 49.50, 51.05
