#
# Makefile for Proj3
# Author: Eleanor Elkus eelkus01
# Date Created: 3/38/23
#
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

zap: main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o
	${CXX} ${LDFLAGS} -o zap main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o

main.o: main.cpp HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c main.cpp

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h HuffmanTreeNode.h BinaryIO.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

unit_test: unit_test_driver.o phaseOne.o ZapUtil.o HuffmanTreeNode.o HuffmanCoder.o
	$(CXX) unit_test_driver.o phaseOne.o ZapUtil.o HuffmanTreeNode.o HuffmanCoder.o

ZapUtil.o: ZapUtil.h HuffmanTreeNode.h

ZapUtilExample.o: ZapUtilExample.cpp ZapUtil.h HuffmanTreeNode.h
ZapUtilExample.out: ZapUtilExample.o HuffmanTreeNode.o ZapUtil.o
	clang++ -g3 -o $@ $^

clean:
	rm *.o *~ a.out

provide:
	provide comp15 proj3_zap README Makefile unit_tests.h main.cpp HuffmanCoder.h\
							HuffmanCoder.cpp countTest countTest2 countTest3 codeTest\
							codeTest2 BinaryIO.h demo.output demoOutput.txt\
							fig1tree.txt HuffmanTreeNode.h my.output myOutput.txt\
							my.stderr my.stdout
