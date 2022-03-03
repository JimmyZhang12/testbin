CXX = g++
CXXFLAGS = -static -O3
INC=-I/usr/include/eigen3

all: main

main: mm_eigen.o
	$(CXX) $(CXXFLAGS) mm_eigen.o -o mm_eigen

mm_eigen.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c main.cpp -o mm_eigen.o

clean:
	rm -f mm_eigen.o