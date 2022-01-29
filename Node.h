/*
 * Node.h
 * Auguste Brown
 * COMP15
 * Spring 2020
 *
 * Contains a definition of the Node struct, which is used by the Graph class
 */

#ifndef NODE_H
#define NODE_H

#include "Location.h"
#include <vector>

struct Node
{
    std::string name;
    Location location;
    std::vector<Node *> neighbors;
    bool visited;
    Node *prev;
};
#endif