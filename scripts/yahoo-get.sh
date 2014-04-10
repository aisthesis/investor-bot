#!/bin/bash
#
# Usage:
# > ./yahoo-get.sh f
# Retrieves OHLC and volume for ticker symbol 'f' from 1974-01-01 to 2014-03-09
# and stores the data in the file '../data/f.csv' 
# 
# The following command downloads historical data from yahoo! into a csv in the data directory
# curl "http://ichart.finance.yahoo.com/table.csv?s=f&a=0&b=1&c=2013&d=5&e=27&f=2013" > ../data/$1.csv
# Stock is Ford (s=f)
# Start date is 2010-07-29 (a=6 [months are counted starting with 0], b=29 [day], c=2010 [year])
# End date is 2011-10-27 (d=9 [month], e=27 [day], f=2011 [year]).
# Output columns are Date, Open High, Low, Close, Volume, Adj Close [?]
# http://ichart.finance.yahoo.com/table.csv?s=f&a=6&b=29&c=2010&d=9&e=27&f=2011&g=d&ignore=.csv
# Similarly:
# http://ichart.finance.yahoo.com/table.csv?s=f&a=0&b=1&c=2013&d=5&e=27&f=2013
 
curl "http://ichart.finance.yahoo.com/table.csv?s=$1&a=0&b=1&c=1946&d=4&e=1&f=2014" > ../data/$1.csv
