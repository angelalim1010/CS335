//Angela Lim
//Header file for part 1

#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits.h>
#include "Graph.h"
using namespace std;

// Deals with graphs txt files
void ReadGraphFile(const string &graph_filename, Graph &graph) {
	ifstream inFile(graph_filename);
	if(inFile.fail()) {
		cout << " Error while opening. ";
		exit(1);
	}
	int vertex1, vertex2; //vertex number
	double weight;
	string file_line;
	getline(inFile, file_line); //skips the first line
	while(getline(inFile, file_line)) {
		//read from string of each line
		stringstream ss(file_line);
		ss >> vertex1;
		graph.addVertex(vertex1);
		while(ss >> vertex2 >> weight) {
			graph.addVertex(vertex2);
			graph.addEdge(vertex1, vertex2, weight);
		}
	}
}



void ReadQueriesFile(const string &query_filename, Graph &graph) {
	ifstream inFile(query_filename);
	int vertex1, vertex2;
	double weight = 0;
	if(inFile.fail()) {
		cout << " Error while opening. ";
		exit(1);
	}
	while(inFile >> vertex1 >> vertex2) {
		//if vertex is adjacent get the weight
		if (graph.isAdj(vertex1,vertex2)) {
			weight = graph.getWeight(vertex1, vertex2);
		}
		//print the weight
		if (weight != 0) {
			cout << vertex1 << " " << vertex2 << ": is connected, weight of the edge is " << weight << endl;
			weight = 0;
		}
		else
			cout << vertex1 << " " << vertex2 << ": is not connected" << endl;
	}
}

#endif //GRAPH_FUNC
