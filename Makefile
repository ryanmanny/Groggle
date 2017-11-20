# Hacked up by Aaron Crandall, 2017
# Modified by Ryan for his own uses :)

# Variables
GPP     = g++
CFLAGS  = -g -Wall -std=c++11
RM      = rm -f
BINNAME = groggle

# Shell gives make a full user environment
SHELL := /bin/bash

# Default is what happenes when you call make with no options
#  In this case, it requires that 'all' is completed
default: all

# All is the normal default for most Makefiles
#  In this case, it requires that build is completed
all: build

# build depends upon *.cpp, then runs the command:
#  g++ -g -std=c++0x -o bigFiveList
build: *.cpp
	$(GPP) $(CFLAGS) -o $(BINNAME) *.cpp

run: build
	./$(BINNAME)

# If you call "make clean" it will remove the built program
clean:
	$(RM) $(BINNAME)
