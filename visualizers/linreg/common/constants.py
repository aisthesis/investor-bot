"""
Constants for linear regression visualizations

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.
"""

DOW_EQUITIES = ['AXP', 'AAPL', 'BA', 'CAT', 'CSCO', 'CVX', 'DD', 'DIS', 
    'GE', 'GS', 'HD', 'IBM', 'INTC', 'JNJ', 'KO', 'JPM', 'MCD', 'MMM',
    'MRK', 'MSFT', 'NKE', 'PFE', 'PG', 'TRV', 'UNH', 'UTX', 'VZ', 'V',
    'WMT', 'XOM']
# http://www.stockmarketsreview.com/thread/dow-jones-30-companies-list-165/
# http://money.cnn.com/data/dow30/
DOW_BY_SECTOR = {
        'Consumer Discretionary': ['DIS', 'HD', 'MCD', 'NKE'],
        'Consumer Staples': ['KO', 'PG', 'WMT'],
        'Energy': ['CVX', 'XOM'],
        'Finance': ['AXP', 'GS', 'JPM', 'TRV', 'V'],
        'Health Care': ['JNJ', 'MRK', 'PFE', 'UNH'],
        'Industrials': ['BA', 'CAT', 'DD', 'GE', 'MMM', 'UTX'], 
        'Information Technology': ['AAPL', 'CSCO', 'IBM', 'INTC', 'MSFT'],
        'Telecommunications': ['VZ']
        }
# learning and test equities were found by randomly selecting
# half (rounded down) of the equities in each sector
DOW_LEARN = ['AAPL', 'AXP', 'BA', 'CAT', 'DD', 'HD', 'JNJ', 'MSFT', 
        'NKE', 'PFE', 'PG', 'V', 'XOM']
DOW_TEST = ['CSCO', 'CVX', 'DIS', 'GE', 'GS', 'IBM', 'INTC', 'JPM', 
        'KO', 'MCD', 'MMM', 'MRK', 'TRV', 'UNH', 'UTX', 'VZ', 'WMT']
