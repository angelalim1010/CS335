Implemented all three parts with a separate Graph class because it is easier to implement
Files include: Graph.h
               Graph.cc

Part 1:
Implemented big 5

Created getWeight, getCost, exists, isAdj, addvertex, addEdge
Used a struct in private that also uses a hash map

Part 2:
Created a method for Dijkstra and printPath method

Part 3:
Added randomGraph method

To run:
make all
./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt
./CreateGraphAndTest Graph2.txt AdjacencyQueries2.txt
./FindPaths Graph2.txt 1
./FindPaths Graph3.txt 1
./TestRandomGraph 100

To remove obj files:
make clean
