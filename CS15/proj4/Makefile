#
# Makefile for Proj4
# Authors: Eleanor Elkus (eelkus01) and Talia Tepper (tteppe01)
# Date Created: 4/13/23
#
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: main.o gerp.o DirNode.o FSTree.o stringProcessing.o
	${CXX} ${LDFLAGS} -O2 -o gerp main.o gerp.o DirNode.o FSTree.o stringProcessing.o

gerp.o: gerp.cpp gerp.h stringProcessing.h DirNode.h FSTree.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

main.o: main.cpp gerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o treeTraversal FSTreeTraversal.o FSTree.o DirNode.o

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

FSTree.o: FSTree.h DirNode.h

DirNode.o: DirNode.h

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

unit_test: unit_test_driver.o stringProcessing.o
	$(CXX) unit_test_driver.o stringProcessing.o

provide:
	provide comp15 proj4_gerp Makefile README gerp.cpp gerp.h\
			stringProcessing.h stringProcessing.cpp main.cpp unit_tests.h\
			a.txt b.txt cmds1.txt filecmd1.txt myOutput.txt myOutput2.txt\
			my.stderr output.out

