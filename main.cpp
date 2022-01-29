/*
 * main.cpp
 * Auguste Brown
 * COMP15
 * Spring 2020
 *
 * Implements functionality for list, dist, path, and quit functions
 * in FlooHub
 */

#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void readVertices(string filename, Graph &g);
void readEdges(string filename, Graph &g);
double convertLocation(int degrees, int minutes);
void handleInput(string input, Graph &g);
void controlLoop(Graph &g);
void list(Graph &g);
void dist(Graph &g, string from, string to);
void path(Graph &g, string from, string to, int max_paths);

int main(int argc, char const *argv[])
{
    if (argc != 3){
        cerr << "Usage: findpath vertex_data edge_data\n";
        exit(1);
    }
    string vertices_file = argv[1];
    string edges_file = argv[2];
    Graph student_map;
    readVertices(vertices_file, student_map);
    readEdges(edges_file, student_map);
    // set decimal precision
    cout << fixed;
    cout << setprecision(2);
    controlLoop(student_map);
}

// Name: readVertices
// Purpose: Reads the vertex data from a file and populates the graph with
//          the approproate data
// Parameters: Name of file to read from, reference to graph to populate
// Returns: None
// Effects: Creates a new node for each line in the file and adds it to the
//          graph
void readVertices(string filename, Graph &g){
    ifstream input;
    string line, name;
    int lat_deg, lat_min, lon_deg, lon_min;
    input.open(filename);
    if (not input.is_open()){
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }

    while (not getline(input, line).eof()){
        stringstream line_ss(line);
        line_ss >> name >> lat_deg >> lat_min >> lon_deg >> lon_min;
        g.addNode(name, convertLocation(lat_deg, lat_min),
                 convertLocation(lon_deg, lon_min));
    }

    input.close();
}

// Name: readEdge
// Purpose: Reads the edge data from a file and populates the Nodes with
//          the correct edges
// Parameters: Name of file to read from, reference to graph to populate
// Returns: None
// Effects: Creates a new edge for each line in the file
void readEdges(string filename, Graph &g){
    ifstream input;
    string line, from, to;
    input.open(filename);
    if (not input.is_open()){
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }

    while (not getline(input, line).eof()){
        stringstream line_ss(line);
        line_ss >> from >> to;
        g.addEdge(from, to);
    }

    input.close();
}

// Name: convertLocation
// Purpose: Takes a location in degrees and minutes and converts it to decimal
//          format
// Parameters: int degrees, int minutes representing a location
// Returns: double equivalent of the location
// Effects: None
double convertLocation(int degrees, int minutes){
    if (degrees < 0)
        return degrees - (minutes / 60.0);
    else
        return degrees + (minutes / 60.0);
}

// Name: handleInput
// Purpose: Handles logic to handle commands entered by the user
// Parameters: User input, graph
// Returns: None
// Effects: Prints to the console
void handleInput(string input, Graph &g){
    stringstream input_ss(input);
    string command;
    input_ss >> command;
    if (command == "list"){
        list(g);
    }
    else if (command == "dist"){
        string from, to;
        input_ss >> from >> to;
        dist(g, from, to);
    }
    else if (command == "path"){
        string from, to;
        int num_paths;
        input_ss >> from >> to >> num_paths;
        path(g, from, to, num_paths);
    }
    
    if (command != ""){
        cout << "-EOT-\n";
    }
}

// Name: controlLoop
// Purpose: Contains the main control loop which gets input from the user and
//          sends them to handleInput
// Parameters: A reference to the graph g
// Returns: None
// Effects: None
void controlLoop(Graph &g){
    string input;
    while (!(getline(cin, input).eof()) and input != "quit") {
        handleInput(input, g);
    }
}

// Name: list
// Purpose: Implements the list functionality
// Parameters: A reference to the graph g
// Returns: None
// Effects: Lists the nodes in graph g on the console
void list(Graph &g){
    g.listNodes();
}

// Name: dist
// Purpose: Implements the dist functionality
// Parameters: A reference to the graph g, the names of the two nodes
// Returns: None
// Effects: Prints the distance between the two nodes on the console
void dist(Graph &g, string from, string to){
    cout << g.distance(from, to) << endl;
}

// Name: path
// Purpose: Implements the path functionality
// Parameters: A reference to the graph g, the names of the two nodes,
//             and the max number of paths to find
// Returns: None
// Effects: Prints the requested paths between the two nodes on the console
void path(Graph &g, string from, string to, int max_paths){
    g.findPaths(from, to, max_paths);
}

