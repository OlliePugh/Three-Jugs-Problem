#ifndef _JUGH_
#define _JUGH_

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

#endif