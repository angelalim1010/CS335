//Angela Lim
//C++ file for part 2
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits.h>
#include "GraphFunctions.h"
using namespace std;


int main(int argc, char **argv){
	if(argc !=3){
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <STARTING_VERTEX>" << endl;
		return 0;
	}
	if(stoi(argv[2]) < 0){
		cout << "invalid starting vertex" <<endl;
		return 0;
	}

	Graph graph;
	const string graph_file(argv[1]);
	const int starting_vertex(stoi(argv[2]));
	ReadGraphFile(graph_file, graph);
	graph.Dijkstra(starting_vertex);


}
