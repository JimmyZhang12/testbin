CXX = g++
CXXFLAGS = -static

all: main

# short: short.cpp
# 	$(CXX) -O3 -g -c short.cpp

# fast: CXXFLAGS += -O3 -faggressive-loop-optimizations -DFAST
# fast: main.fast

# main.fast: matrix_mult.o
# 	$(CXX) $(CXXFLAGS) matrix_mult.o -o matrix_mult.fast -lm

BOOST_DIR="/home/jimmyjz2/passat/custom_testbin/boost_1_77_0/boost"

main: graph.o
	$(CXX) $(CXXFLAGS) build/graph.o -o graph_dfs -lm -I${BOOST_DIR}

graph.o: main.cpp

	$(CXX) $(CXXFLAGS) -c main.cpp -o build/graph.o

clean:
	rm build/graph.o
