# Makefile for Binary Search Tree Assignment

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 

bst: main.o BinarySearchTree.o
	${CXX} -o $@ $^

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h
	${CXX} ${CXXFLAGS} -c BinarySearchTree.cpp

unit_tests: unit_tests.o BinarySearchTree.o
	${CXX} ${CXXFLAGS} -o unit_tests unit_tests.o BinarySearchTree.o

clean:
	rm -rf bst *.o *.dSYM

