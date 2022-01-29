/*
 * Graph.h
 * Auguste Brown
 * COMP15
 * Spring 2020
 *
 * Contains the definition of the Graph class. See details in Graph.cpp
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <vector>
#include <queue>

class Graph
{
    public:
        Graph();
        ~Graph();
        void addNode(std::string name, double lat, double lon);
        void addEdge(std::string from, std::string to);
        void listNodes();
        double distance(std::string from, std::string to);
        void findPaths(std::string from, std::string to, int max_paths);
    private:
        std::vector<Node*> nodes;

        Node *findNode(std::string name);
        bool findPaths(Node *from, Node *to, int max_paths, int &num_paths);
        void printPath(Node *last_node, int path_num);
        void printNode(Node *node);
};
#endif