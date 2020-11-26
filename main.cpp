#include <iostream>
#include <array>
#include <unordered_set>

#include "jug.h"
#include "node.h"

using namespace std;

int main() {

    array<Jug, Node::getJugCount()> startingJugs = {Jug(10), Jug(3), Jug(4)};

    startingJugs[0].setLevel(3);
    startingJugs[1].fill();

    Node startingPoint = Node(startingJugs);

    array<Jug, Node::getJugCount()> startingJugs2 = {Jug(10), Jug(3), Jug(4)};

    startingJugs2[0].setLevel(3);
    startingJugs2[1].fill();

    Node startingPoint2 = Node(startingJugs2);

    unordered_set<Node> uniqueJugs = {startingPoint};

    cout << uniqueJugs.count(startingPoint2) << endl;

    startingPoint.genChildren();

    array<Node*, Node::getJugCount() * Node::getJugCount()> children = startingPoint.getChildren();

    for (size_t i = 0; i < startingPoint.getChildren().size(); i++) {
        cout << children[i]->toString() << endl;
        children[i]->genChildren();
    }
    return 0;
}