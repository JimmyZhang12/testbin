#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>                         

#include "roadNetCA.hh"

using namespace boost;
using namespace std;

typedef adjacency_list<boost::listS, boost::vecS, boost::undirectedS> UndirectedGraph;
typedef std::pair<int, int> Edge;
typedef boost::graph_traits<UndirectedGraph>::vertex_descriptor MyVertex;


class MyVisitor : public boost::default_dfs_visitor
{
public:
  std::set<MyVertex>visited;
  void discover_vertex(MyVertex v, const UndirectedGraph& g) const
  {
    return;
  }
};

int main(int argc, char *argv[])
{


    int max_edges = 2000000;

    int option;
    while((option = getopt(argc, argv, "n:")) != -1){ //get option from the getopt() method
        switch(option){
            case 'n':
                max_edges = atoi(optarg);
                break;
      }
   }
    
    UndirectedGraph g;
    assert(max_edges > 0);
    for (int i = 0; i<max_edges; i++){
        if (i%100000 == 0)
            cout << "num edges: " << i << '\n';
        int src = roadnet_ca::src[i];
        int dst = roadnet_ca::dst[i];
        add_edge(src,dst,g);

    }


    std::cout <<"num vertices: "<<num_vertices(g) << "\n" 
        <<"num edges: "<<num_edges(g) << "\n";
    std::cout <<"Traversing graph with DFS!\n";

    boost::default_dfs_visitor vis;
    // MyVisitor vis;
    boost::depth_first_search(g, boost::visitor(vis));
    std::cout <<"done!\n";

    return 0;
}