#ifndef _NODEH_
#define _NODEH_

#include <array>
#include <vector>
#include "jug.h"

using namespace std;

class Node {
    // Stores the combination of jugs in the graph
    private:
        static const int jugCount = 3;
        array<Jug, jugCount> jugs;  // point to array of jugs
        vector<Node*> children;
        Node* parent;  // pointer to parent

    public:
        Node() {};
        Node(array<Jug, jugCount> &jugs, Node*);
        Node(array<Jug, jugCount> &_jugs) { jugs = _jugs;};
        array<Jug, jugCount> getJugs() const { return jugs; };
        vector<Node*> getChildren() const { return children; };  
        void genChildren();
        std::string toString();
        constexpr static size_t getJugCount() { return Node::jugCount; };
        bool operator==(const Node&) const;
        bool containsChild(Node*);
        bool addChild(Node*);
};

namespace std {
    template<> struct hash<Node> {  // add hash function to std for Node class
        size_t operator()(const Node &node) const {
            int sumLevel = 0;
            for (size_t i = 0; i < node.getJugs().size(); i++) {
                sumLevel += node.getJugs()[i].getLevel();
            }
            return sumLevel;  
        }
    };
}

#endif