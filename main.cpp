#include <iostream>
#include <array>
#include <unordered_set>

#include "jug.h"
#include "node.h"

using namespace std;

void DFS(unordered_set<Node>* terminals, Node currentNode) {
    if (terminals->count(currentNode) == 0) {
        terminals->insert(currentNode);  // add the node to the set
    }
    else {
        return;  // stop going down this path and pursue the next path
    }
    currentNode.genChildren();  // generate the chidren for that node

    for (size_t i = 0; i < currentNode.getChildren().size(); i++) {
        Node* child = currentNode.getChildren()[i];
        if (terminals->count(*child) == 0) {
            DFS(terminals, *child);
        }
    }
    
}

int main() {
    int jugSizes[3];
    
    for (size_t i = 0; i < sizeof(jugSizes)/sizeof(jugSizes[0]); i++)
    {
        cout << "Please enter a size for jug " << i << " ";
        cin >> jugSizes[i];
    }

    array<Jug, Node::getJugCount()> startingJugs = {Jug(jugSizes[0]), Jug(jugSizes[1]), Jug(jugSizes[2])};

    Node startingPoint = Node(startingJugs);

    unordered_set<Node> uniqueJugs;

    DFS(&uniqueJugs, startingPoint);

    cout << uniqueJugs.size() << endl;

    return 0;
}