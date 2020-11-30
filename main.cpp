#include <iostream>
#include <array>
#include <unordered_set>

#include "jug.h"
#include "node.h"

using namespace std;

void DFS(unordered_set<Node>* terminals, Node currentNode) {
    if (terminals->count(currentNode) == 0) {  // if the combintaion of jugs is new
        terminals->insert(currentNode);  // add the node to the set
    }
    else {  // we have already seen this combination of jugs
        delete &currentNode;  // no longer needs to be stored
        return;  // stop going down this path and pursue the next path
    }
    currentNode.genChildren();  // generate the chidren for that node

    for (size_t i = 0; i < currentNode.getChildren().size(); i++) {
        Node* child = currentNode.getChildren()[i];  // get the current child that is being analysed
        if (terminals->count(*child) == 0) {  // if the combination of jugs is not in the map
            DFS(terminals, *child);  // recursive function to the next 
        }
    }
}

int main() {
    int jugSizes[3];  // store the values of the user defined jug sizes
    
    for (size_t i = 0; i < sizeof(jugSizes)/sizeof(jugSizes[0]); i++)
    {
        cout << "Please enter a size for jug " << i << " ";
        cin >> jugSizes[i];  // store the users input
    }

    array<Jug, Node::getJugCount()> startingJugs = {Jug(jugSizes[0]), Jug(jugSizes[1]), Jug(jugSizes[2])};

    Node startingPoint = Node(startingJugs);

    unordered_set<Node> uniqueJugs;  // unordered_set for performance
    /* i am also using an set because an array can have multiple occurances of an elemnt
    whereas elements in a set must be unique*/

    DFS(&uniqueJugs, startingPoint);  // start the recursive function

    cout << uniqueJugs.size() << endl;  // output the amount of unique jug combinations generated

    return 0;
}