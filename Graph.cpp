/*
 * Graph.cpp
 * Auguste Brown
 * COMP15
 * Spring 2020
 *
 * Contains the implementation of the Graph class, which stores interconnected
 * nodes. Graph contains some extra functions, such as the ability to list all
 * the nodes, and find the distance between two given nodes
 */

#include "Graph.h"
#include <iostream>

using namespace std;

// Name: Graph
// Purpose: Constructor for the Graph class
// Parameters: None
// Returns: None
// Effects: Initializes instance of Graph class
Graph::Graph(){
    //vector initializes itself
}

// Name: ~Graph
// Purpose: Destructor for the Graph class
// Parameters: None
// Returns: None
// Effects: Recycles all memory used by an instance of the Graph class
Graph::~Graph(){
    for (size_t i = 0; i < nodes.size(); i++){
        delete nodes[i];
    }
}

// Name: addNode
// Purpose: Creates a new node in the graph
// Parameters: Name of node, geograohic location in latitude, longitude
// Returns: None
// Effects: Adds a new node to the graph
void Graph::addNode(string name, double lat, double lon){
    Node *new_node = new Node;
    new_node->name = name;
    new_node->location = Location(lat, lon);
    new_node->visited = false;
    new_node->prev = NULL;
    nodes.push_back(new_node);
}

// Name: addEdge
// Purpose: Creates a new edge in the graph
// Parameters: Name of starting node, name of ending node
// Returns: None
// Effects: Adds a new edge to the graph
void Graph::addEdge(string from, string to){
    Node *from_node = findNode(from);
    Node *to_node = findNode(to);

    from_node->neighbors.push_back(to_node);
}

// Name: listNodes
// Purpose: Lists the names of all nodes on the console
// Parameters: None
// Returns: None
// Effects: Prints to the console
void Graph::listNodes(){
    for (size_t i = 0; i < nodes.size(); i++){
        cout << nodes[i]->name << endl;
    }
}

// Name: findNode
// Purpose: Finds the node in the graph with the given name
// Parameters: Name of node
// Returns: A pointer to the node with the input name
// Effects: None
// Notes: This function is private
Node *Graph::findNode(std::string name){
    for (size_t i = 0; i < nodes.size(); i++){
        if (nodes[i]->name == name){
            return nodes[i];
        }
    }

    return NULL;
}

// Name: distance
// Purpose: Gets the geographic distance between two nodes
// Parameters: Name of both nodes
// Returns: A double — the distance between the two nodes
// Effects: None
double Graph::distance(string from, string to){
    Node *from_node = findNode(from);
    Node *to_node = findNode(to);
    if (from_node == NULL or to_node == NULL){
        return -1.00;
    }
    else {
        return from_node->location.distance_to(to_node->location);
    }
}

// Name: findPaths
// Purpose: Find max_paths number of paths between the Nodes from and to
// Parameters: Name of both nodes, int max number of paths to print
// Returns: None
// Effects: Prints to the console
void Graph::findPaths(string from, string to, int max_paths){
    Node *from_node = findNode(from);
    Node *to_node = findNode(to);
    if (from_node == NULL or to_node == NULL){
        cout << "ERROR: unknown city\n";
        return;
    }

    int num_paths = 0;
    if (!findPaths(from_node, to_node, max_paths, num_paths)){
        cout << "ERROR: no-path-possible\n";
    }
}

// Name: findPaths
// Purpose: Recursive helper function for void findPaths
// Parameters: Pointer to both nodes, int max number of paths to print
//             reference to int number of paths already found
// Returns: true if at least one path was found, false otherwise
// Effects: Prints to the console
bool Graph::findPaths(Node *from, Node *to, int max_paths, int &num_paths){
    if (from == to){ //base case: if we have found the end node
        num_paths++;
        printPath(to, num_paths);
        cout << endl;
        from->prev = NULL;
        return true;
    }

    from->visited = true; //mark the current node
    bool found_path = false;

    for (size_t i = 0; i < from->neighbors.size(); i++) {
        if (!from->neighbors[i]->visited and (max_paths - num_paths) > 0){
            from->neighbors[i]->prev = from;
            if(findPaths(from->neighbors[i], to, max_paths, num_paths))
                found_path = true;
        }
    }
    //reset parameters
    from->visited = false;
    from->prev = NULL;
    return found_path;
}

// Name: printPath
// Purpose: Prints a path
// Parameters: A pointer to the last Node in the path, the number of
//             the current path
// Returns: None
// Effects: Prints to the console
void Graph::printPath(Node *last_node, int path_num){
    if (last_node == NULL){ //if we have found the front of the path
        cout << "PATH " << path_num << " ::";
        return;
    }

    printPath(last_node->prev, path_num); //print previous node first,
    printNode(last_node);                 //then print current node
}

// Name: printNode
// Purpose: Helper function for printPath. Prints the details of a Node in the
//          path       
// Parameters: A pointer to the Node
// Returns: None
// Effects: Prints to the console
void Graph::printNode(Node *node){
    int distance = 0;
    if (node->prev != NULL){
        distance = node->prev->location.distance_to(node->location);
    }

    cout << " " << distance << " " << node->name << " ";
    node->location.print();
}

