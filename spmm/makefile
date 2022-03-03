CXX = g++
CXXFLAGS = -O3 -ggdb3 -static
INC=-I/usr/include/eigen3


all: main

main: spmm.o
	$(CXX) $(CXXFLAGS) spmm.o -o spmm

spmm.o: spmm.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c spmm.cpp -o spmm.o

clean:
	rm -f spmm.o