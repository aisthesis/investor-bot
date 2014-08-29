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
ROOTDIR = ../../
PROG1 = investor
PROG1FLAGS = -I$(ROOTDIR)lib/utils/include
PROG1OBJDEPS = $(ROOTDIR)lib/utils/obj/portfolio.o $(ROOTDIR)lib/utils/obj/order.o
ODIR = obj
BDIR = bin
CPPFLAGSTEST = $(CPPFLAGS)

vpath %.cpp src tst

.PHONY: all
all: directories $(PROG1)_test

.PHONY: directories
directories:
	mkdir -p ./$(BDIR)
	mkdir -p ./$(ODIR)

# Investor
$(PROG1)_test: $(ODIR)/$(PROG1)_test.o $(ODIR)/$(PROG1).o $(PROG1OBJDEPS)
	$(CC) $(CFLAGS) $(PROG1FLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG1).o: $(PROG1).cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PROG1FLAGS) -c $< -o $@

$(ODIR)/$(PROG1)_test.o: $(PROG1)_test.cpp directories
	$(CC) $(CFLAGS) $(CPPFLAGSTEST) $(PROG1FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*
