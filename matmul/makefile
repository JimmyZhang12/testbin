CXX = g++
CXXFLAGS = -static

all: main

short: short.cpp
	$(CXX) -O3 -g -c short.cpp

fast: CXXFLAGS += -O3 -faggressive-loop-optimizations -DFAST
fast: main.fast

main.fast: matrix_mult.o
	$(CXX) $(CXXFLAGS) matrix_mult.o -o matrix_mult.fast -lm

main: matrix_mult.o
	$(CXX) $(CXXFLAGS) matrix_mult.o -o matrix_mult -lm

matrix_mult.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o matrix_mult.o

clean:
	rm matrix_mult.o