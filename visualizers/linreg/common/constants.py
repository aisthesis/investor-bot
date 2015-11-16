"""
Constants for linear regression visualizations

Copyright (c) 2015 Marshall Farrier

Distribution and use of this software without prior written permission
of the authors is strictly prohibitied and will be prosecuted to
the full extent of the law.
"""

# http://www.stockmarketsreview.com/thread/dow-jones-30-companies-list-165/
# http://money.cnn.com/data/dow30/
# learning and test equities were found by randomly selecting
# half (rounded down) of the equities in each sector
DOW = {
    'path': '../dow',
    'all': ['AXP', 'AAPL', 'BA', 'CAT', 'CSCO', 'CVX', 'DD', 'DIS', 
        'GE', 'GS', 'HD', 'IBM', 'INTC', 'JNJ', 'KO', 'JPM', 'MCD', 'MMM',
        'MRK', 'MSFT', 'NKE', 'PFE', 'PG', 'TRV', 'UNH', 'UTX', 'VZ', 'V',
        'WMT', 'XOM'],
    'sectors': {
        'Consumer Discretionary': ['DIS', 'HD', 'MCD', 'NKE'],
        'Consumer Staples': ['KO', 'PG', 'WMT'],
        'Energy': ['CVX', 'XOM'],
        'Finance': ['AXP', 'GS', 'JPM', 'TRV', 'V'],
        'Health Care': ['JNJ', 'MRK', 'PFE', 'UNH'],
        'Industrials': ['BA', 'CAT', 'DD', 'GE', 'MMM', 'UTX'], 
        'Information Technology': ['AAPL', 'CSCO', 'IBM', 'INTC', 'MSFT'],
        'Telecommunications': ['VZ']
        },
    'learn': ['AAPL', 'AXP', 'BA', 'CAT', 'DD', 'HD', 'JNJ', 'MSFT', 
        'NKE', 'PFE', 'PG', 'V', 'XOM'],
    'test': ['CSCO', 'CVX', 'DIS', 'GE', 'GS', 'IBM', 'INTC', 'JPM', 
        'KO', 'MCD', 'MMM', 'MRK', 'TRV', 'UNH', 'UTX', 'VZ', 'WMT']
    }
SP500_SIZES = [{'train': 32, 'test': 32}]

START = '1995'
END = '2016'
N_FEAT_SESS = 256
PRICE_COL = 'Adj Close'
# the following numbers represent the powers of 2 to be used--
# i.e., 2**5 to 2**9 (32, 64, 128, 256, 512)
# end is one past the last value used
PRED_RANGE_BEGIN = 5
PRED_RANGE_END = 10

MODEL_FILE = 'model.npz'
MODEL_FILE_TEMPLATE = 'model{:02d}.npz'
SUMMARY_FILES = {'train': 'IN_SAMPLE', 'test': 'OUT_OF_SAMPLE'}
