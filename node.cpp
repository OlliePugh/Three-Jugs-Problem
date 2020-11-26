#include <array>
#include <string>
#include "node.h"

using namespace std;

Node::Node(array<Jug, jugCount> &jugs, Node *parent) {
    this->jugs = jugs;
    this->parent = parent;
    this->visited = false;
}

bool Node::operator== (const Node &otherNode) const{
    for (size_t i = 0; i < this->jugs.size(); i++) {  // for each element in the array
        if (this->jugs[i].getLevel() != otherNode.getJugs()[i].getLevel()) {
            return false;  // the jugs do not match therefore theyre not identical
        }
    }
    return true;
}

void Node::genChildren() {
    int counter = 0;
    for (size_t i = 0; i < this->jugs.size(); i++) {
        for (size_t j = 0; j < this->jugs.size(); j++) {
            array<Jug,Node::jugCount> newJugs = this->getJugs();  // copy the contents of the jugs list
            if (i==j) {
                newJugs[i].fill();  // fill from the infinite water source
            }
            else{ 
                newJugs[i].pour(&newJugs[j]);
            }
            this->children[counter++] = new Node(newJugs, this);  // create a new node with the new jugs and the parent as this 
        }
    }
}

string Node::toString() {
    string toReturn = "";
    for (size_t i = 0; i < this->jugs.size(); i++)
    {
       toReturn+= to_string(this->jugs[i].getLevel()) + '/';
    }
    return toReturn;
}