/*
 * testGraph.cpp
 * Auguste Brown
 * COMP15
 * Spring 2020
 *
 * Contains unit tests for the Graph class
 */

#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <iomanip>

using namespace std;

void testAddNode(string name, double lat, double lon, Graph &g);
//void testGetNeighbors(string name, queue<Node> &neighbors);
void testListNodes(Graph &g);
void testDistance(string from, string to, Graph &g);

int main(){
    cerr << fixed;
    cerr << setprecision(2);

    Graph g; //create empty graph
    testListNodes(g);
    testDistance("Here", "There", g);

    testAddNode("Gus", 17, 38, g); //add node
    testListNodes(g);
    testDistance("Gus", "There", g);

    testAddNode("Bus", 17, 39, g); //add another node
    testListNodes(g);
    testDistance("Gus", "Bus", g);
}

// tests the addNode function in Graph.cpp
void testAddNode(string name, double lat, double lon, Graph &g){
    cerr << "Adding node named " << name << " at latitude: " << lat
         << " and longitude: " << lon << endl;
    g.addNode(name, lat, lon);
}

// tests the listNodes function in Graph.cpp
void testListNodes(Graph &g){
    cerr << "Listing nodes::\n";
    g.listNodes();
}

// tests the distance function in Graph.cpp
void testDistance(string from, string to, Graph &g){
    cerr << "The distance from " << from << " to " << to << " is: ";
    cerr << g.distance(from, to) << endl;
}