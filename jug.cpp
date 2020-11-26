#include "jug.h"

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