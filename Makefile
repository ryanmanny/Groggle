# Variables
GPP     = g++
CFLAGS  = -g -Wall -std=c++11
RM      = rm -f
BINNAME = groggle
SOURCE  = Board/*.cpp Groggle/*.cpp WordList/*.cpp main.cpp

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
build: $(SOURCE)
	$(GPP) $(CFLAGS) -o $(BINNAME) $(SOURCE)

run: build
	./$(BINNAME)

# If you call "make clean" it will remove the built program
clean:
	$(RM) $(BINNAME)
