#include <iostream>
#include <unistd.h>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>                    

#include "roadNetCA.hh"

using namespace boost;
using namespace std;

typedef adjacency_list<boost::listS, boost::vecS, boost::undirectedS> UndirectedGraph;
typedef std::pair<int, int> Edge;
typedef boost::graph_traits<UndirectedGraph>::vertex_descriptor MyVertex;
typedef boost::graph_traits<UndirectedGraph>::edge_descriptor MyEdge;

class DFSVisitor : public boost::default_dfs_visitor
{
public:
    int& vTotal;
    int& eTotal;

    DFSVisitor(int& ecount, int& vcount):eTotal(ecount), vTotal(vcount){
        vTotal = 0;
        eTotal = 0;
    }
    void examine_edge(MyEdge v, const UndirectedGraph& g){
        eTotal++;
        return;
    }
    void discover_vertex(MyVertex v, const UndirectedGraph& g){
        vTotal++;
        return;
    }
};

class BFSVisitor : public boost::default_bfs_visitor
{
public:
    int& vTotal;
    int& eTotal;

    BFSVisitor(int& ecount, int& vcount):eTotal(ecount), vTotal(vcount){
        vTotal = 0;
        eTotal = 0;
    }
    void examine_edge(MyEdge v, const UndirectedGraph& g){
        eTotal++;
        return;
    }
    void discover_vertex(MyVertex v, const UndirectedGraph& g){
        vTotal++;
        return;
    }
};

int main(int argc, char *argv[])
{
    int max_edges = 2000000;
    int mode = 0;
    int start_node = 1;

    int option;
    while((option = getopt(argc, argv, "n:m:v:")) != -1){ //get option from the getopt() method
        switch(option){
            case 'n':
                max_edges = atoi(optarg);
                break;
            case 'm':
                mode = atoi(optarg);
                break;
            case 'v':
                start_node = atoi(optarg);
                break;
      }
   }
    
    UndirectedGraph g;
    assert(max_edges > 0);

    for (int i = 0; i<max_edges; i++){
        if (i%100000 == 0)
            cout << "num edges: " << i << '\n';
        add_edge(roadnet_ca::src[i],roadnet_ca::dst[i],g);
    }


    std::cout <<"num vertices: "<<num_vertices(g) << "\n" 
        <<"num edges: "<<num_edges(g) << "\n";
    int ecount = 0;
    int vcount = 0;

    if (mode == 0){
        std::cout <<"Traversing graph with DFS!\n";
        DFSVisitor vis(ecount, vcount);
        boost::depth_first_search(g, boost::visitor(vis));


    }
    else{
        std::cout <<"Traversing graph with BFS!\n";
        BFSVisitor vis(ecount, vcount);
        boost::breadth_first_search(g, start_node, boost::visitor(vis));
    }
    std::cout <<"done!\n";
    std::cout << "Examined " << ecount << " edges!\n";
    std::cout << "Examined " << vcount << " vertices!\n";

    return 0;
}