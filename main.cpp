#include <iostream>
#include <array>
#include <unordered_set>

using namespace std;

class Jug {
    private:
        int size, level;
        
    public:
        Jug() {};
        //~Jug() { cout << "Jug just got deleted from mem"; };
        Jug(int); 
        int getLevel() const { return level; }
        int getSize() const { return size; }
        void setLevel(int _level) { level=_level; }
        void pour(Jug*);
        void empty() { setLevel(0); }
        void fill() { setLevel(size); }  // set to the max capacity
};

Jug::Jug(int size) {
    this->size = size;
    this->level = 0;
}


void Jug::pour(Jug *recvJug) {
    if (recvJug->level + this->getLevel() > recvJug->size) {  // if the water would overflow
        this->setLevel(this->getLevel() - (recvJug->size-recvJug->level));  // set the value of the donor jug to its new level
        recvJug->fill();  // the jug is now full
    }
    else { // enough room in the jug to fill to the top
        recvJug->setLevel(recvJug->level+this->getLevel());
        this->empty();
    }
}

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
        void print();
        constexpr static size_t getJugCount() { return Node::jugCount; };
        bool equals(const Node*);
};

Node::Node(array<Jug, jugCount> &jugs, Node *parent) {
    this->jugs = jugs;
    this->parent = parent;
    this->visited = false;
}

bool Node::equals (const Node *otherNode) {
    for (size_t i = 0; i < this->jugs.size(); i++) {  // for each element in the array
        if (this->jugs[i].getLevel() != otherNode->getJugs()[i].getLevel()) {
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

struct JugListHasher {
    inline size_t operator()(const array<Jug, Node::getJugCount()> &jugs) const {
        int sumLevel = 0;
        for (size_t i = 0; i < jugs.size(); i++) {
            sumLevel += jugs[i].getLevel();
        }
        return sumLevel;  
    }
};

struct JugListEqual {
public:
    bool operator()(const array<Jug, Node::getJugCount()> & list1, const array<Jug, Node::getJugCount()> & list2) const {
        for (size_t i = 0; i < list1.size(); i++) {  // for each element in the array
        if (list1[i].getLevel() != list2[i].getLevel()) {
            return false;  // the jugs do not match therefore theyre not identical
        }
    }
    return true;
    }
};

void Node::print() {
    for (size_t i = 0; i < this->jugs.size(); i++)
    {
       cout << this->jugs[i].getLevel() << '/';
    }
    cout << endl;
}

int main() {

    array<Jug, Node::getJugCount()> startingJugs = {Jug(10), Jug(3), Jug(4)};

    startingJugs[0].setLevel(3);
    startingJugs[1].fill();

    Node startingPoint = Node(startingJugs);

    array<Jug, Node::getJugCount()> startingJugs2 = {Jug(10), Jug(3), Jug(4)};

    startingJugs2[0].setLevel(4);
    startingJugs2[1].fill();

    Node startingPoint2 = Node(startingJugs2);

    unordered_set<array<Jug, 3>, JugListHasher, JugListEqual> uniqueJugs = {startingPoint.getJugs()};

    cout << uniqueJugs.count(startingPoint2.getJugs()) << endl;

    startingPoint.genChildren();

    array<Node*, Node::getJugCount()*Node::getJugCount()> children = startingPoint.getChildren();

    for (size_t i = 0; i < startingPoint.getChildren().size(); i++) {
        children[i]->print();
        children[i]->genChildren();
    }
    
    return 0;
}