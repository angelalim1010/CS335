//Angela Lim
//c++ file for part 1

#include <iostream>
#include <fstream>
#include "GraphFunctions.h"
using namespace std;

int main(int argc, char **argv){
	if(argc !=3){
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <ADJACENCY_QUERIES_FILE>" << endl;
		return 0;
	}

	Graph graph;
	const string graph_file(argv[1]);
	const string queries_file(argv[2]);
	ReadGraphFile(graph_file, graph);
	ReadQueriesFile(queries_file, graph);

}
