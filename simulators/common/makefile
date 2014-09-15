# Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
#
# Distribution and use of this software without prior written permission
# of the authors is strictly prohibitied and will be prosecuted to
# the full extent of the law.
#
# makefile for cpp simulator class
# for investor-bot
#
# Author Marshall Farrier
# Since 2014-09-03

CC = g++
CFLAGS = -g -Wall
CPPFLAGS = -std=c++11 -Iinclude
ROOTDIR = ../../
PROG1 = simulator
PROG2 = sim_runner
# Investor01 is used for testing (Investor is abstract)
PROG1FLAGS = -I$(ROOTDIR)investors/common/include -I$(ROOTDIR)lib/utils/include \
	-I$(ROOTDIR)investors/01/include
PROG1OBJDEPS = $(ROOTDIR)investors/common/obj/investor.o $(ROOTDIR)lib/utils/obj/portfolio.o \
	$(ROOTDIR)lib/utils/obj/order_action.o $(ROOTDIR)lib/utils/obj/order.o \
	$(ROOTDIR)investors/01/obj/investor01.o
PROG2FLAGS = -I$(ROOTDIR)investors/common/include -I$(ROOTDIR)lib/utils/include
ODIR = obj
BDIR = bin
CPPFLAGSTEST = $(CPPFLAGS)

vpath %.cpp src tst

.PHONY: all
all: directories $(PROG1)_test $(ODIR)/$(PROG2).o

.PHONY: directories
directories:
	mkdir -p ./$(BDIR)
	mkdir -p ./$(ODIR)

# Simulator
$(PROG1)_test: $(ODIR)/$(PROG1)_test.o $(ODIR)/test.o $(ODIR)/$(PROG1).o $(PROG1OBJDEPS)
	$(CC) $(CFLAGS) $(PROG1FLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG1).o: $(PROG1).cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PROG1FLAGS) -c $< -o $@

$(ODIR)/$(PROG1)_test.o: $(PROG1)_test.cpp
	$(CC) $(CFLAGS) $(CPPFLAGSTEST) $(PROG1FLAGS) -c $< -o $@

$(ODIR)/test.o: test.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# SimRunner (no executable needed, will be massively tested by running)
$(ODIR)/$(PROG2).o: $(PROG2).cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PROG2FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*
