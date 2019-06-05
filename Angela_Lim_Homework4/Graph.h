//Angela Lim
//Header file for Djikstra and randomGraph + accessors + mutators

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <algorithm>
#include <cstdlib> // for exit and randomGraph
#include <queue> //for djikstra
#include <limits> //for dijkstras
#include <list>
#include <unordered_map>
#include <map>
#include <ctime> //for random numbers

using namespace std;

class Graph {
	public:
		//default big five
		Graph() = default;
		~Graph() = default;
		//copy and move s
		Graph &operator=(const Graph &rhs) = default;
		Graph(Graph &&rhs) = default;
		Graph &operator=(Graph &&rhs) = default;

		//accessor
		//returns the weight between two vertices
		double getWeight(int &from, int &to);
		double getCost(const int v); //returns the current cost of vertex
		bool exists(const int &v);
		bool isAdj(const int &one, const int &two);


		//mutator
        void printPath(const int v); //helps visualize the current graph
		void addVertex(const int &val); //adds vertex num
		void addEdge(const int &from, const int &to, const double &weight);
        //find the shortest path
        void Dijkstra(const int &originVec);
        //create a random undirected graph
		void randomGraph(const size_t numberNodes);


	private:
		struct vertex {
			int value, outdegree = 0;
			double distance;
			vertex* path;
			bool known;
			unordered_map<int, double> adj; //holds the vertex # 
			vertex() : path(nullptr) {}
			vertex(int num) : value(num), path(nullptr) {}
		};

		map<const int, vertex> vertices;
};

#endif //GRAPH_H
