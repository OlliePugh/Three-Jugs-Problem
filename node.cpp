#include <array>
#include <string>
#include "node.h"

using namespace std;

Node::Node(array<Jug, jugCount> &jugs, Node *parent) {
    this->jugs = jugs;
    this->parent = parent;
}

bool Node::operator== (const Node &otherNode) const{  //override the == opertor for the node class
    for (size_t i = 0; i < this->jugs.size(); i++) {  // for each element in the array
        if (this->jugs[i].getLevel() != otherNode.getJugs()[i].getLevel()) {
            return false;  // the jugs do not match therefore theyre not identical
        }
    }
    return true;
}

void Node::genChildren() {  // generate the children of the node
    int counter = 0;
    for (size_t i = 0; i < this->jugs.size(); i++) {  // loop through each possible source of water
        
        array<Jug,Node::jugCount> newJugs = this->jugs;
        newJugs[i].empty();  // throw the water onto the ground
        if (this->addChild(new Node(newJugs, this), counter)) counter++;
        
        for (size_t j = 0; j < this->jugs.size(); j++) {  // loop through each possible destination of water
            array<Jug,Node::jugCount> newJugs = this->jugs;  // copy the contents of the jugs list
            if (i==j) {
                newJugs[i].fill();  // fill from the infinite water source
            }
            else{ 
                newJugs[i].pour(&newJugs[j]);  // pour from i into j 
            }
            if (this->addChild(new Node(newJugs, this), counter)) counter++; // create a new node with the new jugs and the parent as this   
        }
        // also need to add a node to throw the water from jug i onto the ground
    }
}

bool Node::containsChild(Node *node) {
    for (size_t i = 0; i < this->children.size(); i++)
    {
        if (this->children[i] == node ){
            return true;
        }
        else{
            return false;
        }
    }
    
}

bool Node::addChild(Node *node, int index) {  // to reduce duplicates in the list of children
    if (!this->containsChild(node)) {
        this->children[index] = node;
        return true;
    }
    else {
        return false;
    }
}

string Node::toString() {
    string toReturn = "";
    for (size_t i = 0; i < this->jugs.size(); i++)
    {
       toReturn+= to_string(this->jugs[i].getLevel()) + '/';  // add the level of water
    }
    return toReturn;
}