#ifndef _NODEH_
#define _NODEH_

#include <array>
#include "jug.h"

using namespace std;

class Node {
    private:
        static const int jugCount = 3;
        array<Jug, jugCount> jugs;  // point to array of jugs
        array<Node*, jugCount*jugCount> children;
        Node* parent;  // pointer to parent

    public:
        Node() {};
        //~Node() { cout << "Node just got deleted"; };
        Node(array<Jug, jugCount> &jugs, Node*);
        Node(array<Jug, jugCount> &_jugs) { jugs = _jugs; visited = false; };
        array<Jug, jugCount> getJugs() const { return jugs; };
        array<Node*, jugCount*jugCount> getChildren() const { return children; };  
        bool visited;
        void genChildren();
        std::string toString();
        constexpr static size_t getJugCount() { return Node::jugCount; };
        bool operator==(const Node&) const;
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