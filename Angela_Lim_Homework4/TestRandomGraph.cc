//Angela Lim
//C++ file for Part 3

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GraphFunctions.h"
#include "Graph.h"
using namespace std;

int main(int argc, char **argv){
	if(argc !=2){
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << endl;
		return 0;
	}

	Graph graph;
    const size_t maximum_nodes = stoi(argv[1]);
    graph.randomGraph(maximum_nodes);

    return 0;

}
