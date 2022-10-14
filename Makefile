# Makefile for CPS222 Project 2

# Makefiles define rules for making files from other files.
# Rules have the a common form.
#    target:   dependency list
#        command to make target
# Note that the command is only run if the target is older than
# its dependencies.  For example, if a binary is older than the sources
# it is made from, it needs to be recompiled.

# Google Test must be cloned and built.  If it's not in the same parent
# directory (..), change GTEST_ROOT to the actual location.
GTEST_ROOT = ../googletest/googletest
GTEST_MAIN = $(GTEST_ROOT)/make/libgtest_main.a
CPPFLAGS = -I $(GTEST_ROOT)/include -Wall -g
CXXFLAGS = -std=c++11 -g -Wall -Wextra
# -Wall requests more warnings
# -g compiles for debugging

# Tabs are important in makefiles.
# There must be a tab before each command.

# The first rule is the default (the one built by just "make").
# In this case, it builds the unit tests, then builds the command line
# interface (project2), then runs the unit tests.
all:	expression_test project2 test

# This rule makes the binary program from .o files.
# (.o files are made from .cc files using a rule further down.)
# The command uses some special variables:
#   $@  -- the name of the target
#   $^  -- the names of all dependencies (the .o files listed after ":")
project2: expression.o project2.o
	g++ -o $@ $^

# This rule just gives an additional dependency.
# It doesn't have a command, because there's a default rule to make .o from .cc
expression.o:	expression.h

# Build and run the unit tests.  (Googletest needs -pthread on Linux.)
expression_test:	expression_test.o expression.o  $(GTEST_MAIN)
	g++ -o $@ $^ -pthread

# "make test" always runs tests (if they compile), even if they haven't changed
test:	expression_test
	./$<

