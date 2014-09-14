# Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
#
# Distribution and use of this software without prior written permission
# of the authors is strictly prohibitied and will be prosecuted to
# the full extent of the law.
#
# makefile for baseline simulaator sim00
# This simulation takes the baseline recommendations from recommendations/00,
# which always recommends a 'buy', and applies investor01.
#
# Author Marshall Farrier
# Since 2014-09-12

CC = g++
CFLAGS = -g -Wall
CPPFLAGS = -std=c++11 -Iinclude
ROOTDIR = ../../
PROG1 = sim00
PROG1FLAGS = -I$(ROOTDIR)investors/common/include -I$(ROOTDIR)lib/utils/include \
	-I$(ROOTDIR)investors/01/include -I$(ROOTDIR)simulators/common/include
PROG1OBJDEPS = $(ROOTDIR)investors/common/obj/investor.o $(ROOTDIR)lib/utils/obj/portfolio.o \
	$(ROOTDIR)lib/utils/obj/order_action.o $(ROOTDIR)lib/utils/obj/order.o \
	$(ROOTDIR)investors/01/obj/investor01.o $(ROOTDIR)simulators/common/obj/simulator.o \
	$(ROOTDIR)lib/utils/obj/csv_reader.o $(ROOTDIR)lib/utils/obj/finance.o
ODIR = obj
BDIR = bin
CPPFLAGSTEST = $(CPPFLAGS)

vpath %.cpp src

.PHONY: all
all: directories $(PROG1)

.PHONY: directories
directories:
	mkdir -p ./$(BDIR)
	mkdir -p ./$(ODIR)
	mkdir -p ./output

# sim00
$(PROG1): $(ODIR)/$(PROG1).o $(PROG1OBJDEPS)
	$(CC) $(CFLAGS) $(PROG1FLAGS) $^ -o $(BDIR)/$@

$(ODIR)/$(PROG1).o: $(PROG1).cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PROG1FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*
