CXX = g++
CXXFLAGS = -static
BOOST_DIR="/home/jimmyjz2/passat/custom_testbin/boost_1_77_0/boost"

all: main

fast: CXXFLAGS += -O3 -faggressive-loop-optimizations -DFAST
fast: main.fast

main.fast: graph.o
	$(CXX) $(CXXFLAGS) build/graph.o -o graph_dfs.fast -lm -I${BOOST_DIR}


main: graph.o
	$(CXX) $(CXXFLAGS) build/graph.o -o graph_dfs -lm -I${BOOST_DIR}

graph.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/graph.o

clean:
	rm build/graph.o
