CXX = g++
CXXFLAGS = -O3 -ggdb3 -static
INC=-I/usr/include/eigen3


all: main

main: spmm_regular.o
	$(CXX) $(CXXFLAGS) spmm_regular.o -o spmm_regular

spmm_regular.o: spmm_regular.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c spmm_regular.cpp -o spmm_regular.o

clean:
	rm -f spmm_regular.o