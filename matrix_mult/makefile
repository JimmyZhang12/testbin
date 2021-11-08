CXX = g++
CXXFLAGS = -static -g -faggressive-loop-optimizations



main: matrix_mult.o
	$(CXX) $(CXXFLAGS) matrix_mult.o -o matrix_mult -lm

matrix_mult.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o matrix_mult.o

clean:
	rm matrix_mult.o