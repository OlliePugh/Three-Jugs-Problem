#ifndef _JUGH_
#define _JUGH_

class Jug {
    // Stores the level of the jug and provides some methods for moving water around
    private:
        int size, level;
        
    public:
        Jug() {};
        Jug(int); 
        int getLevel() const { return level; }
        int getSize() const { return size; }
        void setLevel(int _level) { level=_level; }  
        void pour(Jug*);  // pour from this jug into another jug
        void empty() { setLevel(0); }  // set the jug to empty
        void fill() { setLevel(size); }  // set to the max capacity
};

#endif