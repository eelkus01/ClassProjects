###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author: Eleanor Elkus eelkus01

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

##
##  --- Delete these comments and put appropriate comments in ---
##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##
## CAUTION:  DO NOT JUST USE THE OLD RULES FOR 'clean'!!!
##           You do NOT want to remove Datum.o!!
##
##  --- Delete these comments and put appropriate comments in ---

## This rule builds the CalcYouLater executable
CalcYouLater: main.o DatumStack.o Datum.o RPNCalc.o parser.o
	$(CXX) $(LDFLAGS) -o CalcYouLater main.o DatumStack.o Datum.o RPNCalc.o parser.o

## This rule build RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h parser.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

## This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

## This rule builds unit_test
unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o
	$(CXX) unit_test_driver.o DatumStack.o Datum.o parser.o

## This rule builds main.o
## Add all other necessary functions as I go
main.o: main.cpp RPNCalc.h DatumStack.h Datum.h parser.h
	$(CXX) $(CXXFLAGS) -c main.cpp

## This rule builds parser.o
parser.o: parser.cpp parser.h Datum.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

## This rule provides final submission
## ADD ALL FILES BEFORE SUBMITTING
provide:
	provide comp15 proj2_calcyoulater DatumStack.h DatumStack.cpp \
								unit_tests.h RPNCalc.h RPNCalc.cpp \
								parser.h parser.cpp main.cpp README \
								Makefile comp_ops.cyl easy_ops.cyl \
								exec.cyl file_test.cyl if_test.cyl \
								many_ops.cyl rstring.cyl

## This rule builds clean (shouldn't delete Datum.o)
clean:
	rm -f CalcYouLater main.o DatumStack.o RPNCalc.o parser.o
