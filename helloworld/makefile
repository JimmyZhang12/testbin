CXX = g++
CXXFLAGS = -O3 -ggdb3 -static


all: main

main: hw.o
	$(CXX) $(CXXFLAGS) hw.o -o hw

hw.o: hw.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c hw.cpp -o hw.o

clean:
	rm -f hw.o