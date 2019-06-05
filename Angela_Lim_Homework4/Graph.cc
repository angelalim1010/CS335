//Angela Lim
//includes part 2 and 3
#include <iostream>
#include "Graph.h"
#include "Greater.h"
#include "disjoint_sets.cc"


double Graph::getWeight(int &from, int &to) {
	if (!isAdj(from,to)) return -1;
	auto v = vertices.find(from);
	return v -> second.adj.find(to) -> second;
}
//returns cost of vertex or the distance
double Graph::getCost(const int v) {
	return vertices[v].distance;
}

void Graph::addVertex(const int &val) {
	// inserts the vertex pair into map
	vertices.insert(pair<int, vertex>(val, vertex(val)));
}

void Graph::addEdge(const int &from, const int &to, const double &weight) {
	auto v = vertices.find(from);
	v -> second.adj.insert(std::pair<int, double>(to, weight));
}

//return true if vertex exists/ is found
bool Graph::exists(const int &v) {
	if(vertices.find(v) == vertices.end()) return false;
	return true;
}

// checks if vertex two is inside vertex one's adjacency list
bool Graph::isAdj(const int &one, const int &two) {
	auto v = vertices.find(one);
	if (!exists(one) || !exists(two)) return false;
	if (v -> second.adj.find(two) == v -> second.adj.end())	return false;
	return true;
}

//prints a linked list of the shortest path for each vertex.
//needed for part 2
void Graph::printPath(const int v) {
	list<int> path;
	if (!exists(v)) cout << "error could not find vertex";
	vertex *vert = &vertices.find(v) -> second;
	while(vert != nullptr) {

		path.push_front(vert -> value);
		vert = vert -> path;
	}
	for (auto &x: path) cout << x << " ";
}
//part 2 implementing Dijkstra for shortest path
void Graph::Dijkstra(const int &originVec) {
	//stores pointers to the vertices in the graph
	std::priority_queue<vertex*, std::vector<vertex*>, Greater<vertex*>> pq;
	if (!exists(originVec)) { cout << "this vector does not exist."; exit(1); }
	const double DOUBLE_MAX = std::numeric_limits<double>::infinity();
	for (auto &v: vertices){
		v.second.distance = DOUBLE_MAX;
		v.second.known = false;
	}
	auto vec = vertices.find(originVec);
	vec -> second.distance = 0; //origin vec always at 0

	pq.push(&vec -> second);
    //endless loop
	while(1) {
		vertex *v = nullptr;
		bool fin = false;
		//while the queue isn't empty, pop the top off
		while (!pq.empty() && !fin) {
			v = pq.top();
			pq.pop();
			if(!v -> known) fin = true;
		}
		if (!fin) break;
		v -> known = true;

		for (auto adj : v->adj)	{
			//pushing second vector to graph
			auto next = vertices.find(adj.first);
			if (next -> second.distance > v -> distance + adj.second) {
				next -> second.distance = v -> distance + adj.second;
				next -> second.path = v;
				pq.push(&next -> second);
			}
		}
	}

	for(int i = 1; i <= vertices.size(); i++) {
		//origin vector cost is 0
		if (i == originVec) cout << i << ": " << i << " (Cost:0)" << endl;
		else {
			double cost = getCost(i);
			//if the cost is max value of a double there's no path
			if (cost == DOUBLE_MAX)
				cout << i << ": No path available" << endl;
			//else continue printing paths
			else {
				cout << i << ": ";
				printPath(i);
				cout << " (Cost: " << cost << ")" << endl;
			}
		}
	}
}

//implemting part 3: generating a random undirected graph
void Graph::randomGraph(const size_t numberNodes){
    DisjSets disjoint_set(numberNodes);
    size_t total_edge = 0;
    //add the vertices
    for (size_t i = 0; i < numberNodes; i++){
        addVertex(i);
    }
    bool less_than_one_vertex = false;
	//if number of nodes is less then one then theres less than one vertex
    if (numberNodes <= 1){
        less_than_one_vertex = true;
    }
    srand(time(0));
    while(!less_than_one_vertex){
		//create 2 random vertex
        const size_t vertex1 = rand()% numberNodes;
        const size_t vertex2 = rand() % numberNodes;
        if(!(vertex1 == vertex2 ||
		isAdj(vertex1, vertex2) || isAdj(vertex2, vertex1) || disjoint_set.find(vertex1) == disjoint_set.find(vertex2) )) {
			// Add edge
			addEdge(vertex1, vertex2, 0);
			addEdge(vertex2, vertex1, 0);
			for (auto &v: vertices) {
				if (v.first == vertex1 || v.first == vertex2) {
					v.second.outdegree++; // increment outdegree
				}
			}
			// Use the Union-find data structure to union the two sets
			disjoint_set.unionSets(vertex1, vertex2);
			total_edge++;
		}
		for (int i = 1; i < numberNodes; i++) {
			if (disjoint_set.find(i-1) != disjoint_set.find(i)) {
				less_than_one_vertex = false;
				break;
			}
			else {
				less_than_one_vertex = true;
			}
		}
	}

	int min = 0;
	int max = 0;
	int average = 0;
	// Calculating min, max, average
	for (auto &v: vertices) {
		if (v.first == 0) {
		 	min = v.second.outdegree;
			max = v.second.outdegree;
		}
		if (min > v.second.outdegree) {
			min = v.second.outdegree;
		}
		if (max < v.second.outdegree) {
			max = v.second.outdegree;
		}
		average += v.second.outdegree;
	}
	average = average/numberNodes;

	// Printing edges
	cout << "The total number of edges: " << total_edge << endl;
	cout << "The smallest outdegree: " << min << endl;
	cout << "The largest outdegree: " << max << endl;
	cout << "The average outdegree: " << average << endl;
}
