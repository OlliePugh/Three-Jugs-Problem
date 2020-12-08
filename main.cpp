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
    array<int, Node::getJugCount()> jugSizes = {8,5,3};  // store the user defined jug sizes
    for (size_t i = 0; i < jugSizes.size(); i++)
    {
        cout << "Please enter a size for jug " << i+1 << " ";
        cin >> jugSizes[i];  // store the users input
    }

    array<Jug, Node::getJugCount()> startingJugs;  // create an array to store the starting jugs

    for (size_t i = 0; i < jugSizes.size(); i++)  // loop through the amount of jugs that are requried per node
    {
        startingJugs[i] = Jug(jugSizes[i]);
    }
    

    Node startingPoint = Node(startingJugs);

    unordered_set<Node> uniqueJugs;  // unordered_set for performance
    /* i am also using an set because an array can have multiple occurances of an elemnt
    whereas elements in a set must be unique*/

    DFS(&uniqueJugs, startingPoint);  // start the recursive function

    cout << uniqueJugs.size() << endl;  // output the amount of unique jug combinations generated
    system("pause");  // show the output to the user and wait for them to exit
    return 0;
}