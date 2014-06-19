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

- <code>docs</code>

    Informational files, such as information on split dates. This data was consistent with
    price behavior except in the case of JPM, where the splits corresponded to those
    shown in the yahoo! chart but not to the splits shown on http://www.stocksplithistory.com/

- <code>&lt;ticker&gt;-splitadj.mat</code>

    Chronologically sorted (ascending order) matlab binary files adjusted to account for splits. These files are based on the data
    from <code>&lt;ticker&gt;.mat</code> and differ from them only in that they are adjusted for splits.
    Due to the disparity of sources for split information, the adjustment was done manually. No adjustment
    has been made for dividends, only for splits.
