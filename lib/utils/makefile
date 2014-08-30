# Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
#
# Distribution and use of this software without prior written permission
# of the authors is strictly prohibitied and will be prosecuted to
# the full extent of the law.
#
# makefile for cpp utility files
# for investor-bot
#
# Author Marshall Farrier
# Since 2014-08-25

CC = g++
CFLAGS = -Wall
CPPFLAGS = -std=c++11 -Iinclude
PROG1 = portfolio
PROG2 = order
ODIR = obj
BDIR = bin
CPPFLAGSTEST = $(CPPFLAGS)

vpath %.cpp src tst

.PHONY: all
all: directories $(PROG1)_test $(PROG2)_test

.PHONY: directories
directories:
	mkdir -p ./$(BDIR)
	mkdir -p ./$(ODIR)

# Portfolio
$(PROG1)_test: $(ODIR)/$(PROG1)_test.o $(ODIR)/$(PROG1).o
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG1).o: $(PROG1).cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(ODIR)/$(PROG1)_test.o: $(PROG1)_test.cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGSTEST) -c $< -o $@

# Order
$(PROG2)_test: $(ODIR)/$(PROG2)_test.o $(ODIR)/$(PROG2).o
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG2).o: $(PROG2).cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(ODIR)/$(PROG2)_test.o: $(PROG2)_test.cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGSTEST) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*