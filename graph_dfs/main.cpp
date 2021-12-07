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

using namespace boost;
using namespace std;

typedef adjacency_list<> UndirectedGraph;
typedef std::pair<int, int> Edge;
typedef boost::graph_traits<UndirectedGraph>::vertex_descriptor MyVertex;


class MyVisitor : public boost::default_dfs_visitor
{
public:
  void discover_vertex(MyVertex v, const UndirectedGraph& g) const
  {
    cout << v << "\n";
    return;
  }
};


int main(int argc, char *argv[])
{
    string fdir = "../data/roadNet-CA.txt";
    int mode = 0;

    int option;
    while((option = getopt(argc, argv, "f:m:")) != -1){ //get option from the getopt() method
        switch(option){
            case  'f':
                fdir = optarg;
                break;
            case 'm':
                mode = atoi(optarg);
      }
   }
    std::cout << "Building graph from: " << fdir << '\n';

    ifstream graph_txt;
    graph_txt.open(fdir);
    assert(graph_txt.is_open());

    UndirectedGraph g;
    std::unordered_map<string, int> node_name2id;

    while(!graph_txt.eof()){
        string line;
        getline(graph_txt,line);
        vector<string> strVec;              
        boost::algorithm::split(strVec,line,is_any_of("\t "),boost::token_compress_on); 
        if (mode == 0){ //ca road network format
            int src = stoi(strVec[0]);
            int dst = stoi(strVec[1]);
            add_edge(src,dst,g);
        }
        else if (mode == 1){ //u of rochester format
            if (line.at(0) == 'r'){
                int src = node_name2id[strVec[2]];
                int dst = node_name2id[strVec[3]];
                add_edge(src,dst,g);
            }
            else if (line.at(0) == 'i'){
                int id = add_vertex(g);
                node_name2id[strVec[1]] = id;
            }
        }

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