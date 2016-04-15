//Gem superclass.

#ifndef GEM_H
#define GEM_H

#include <ncurses.h>


class Gem
{
    private:
        bool falling;
        bool new_gem;    //Set to true on creation.
    public:
        Gem();
        virtual ~Gem();

        void printVoid(int,int,WINDOW*);
        virtual void printGem(int,int,WINDOW*);
        void printShrink1(int,int,WINDOW*);
        void printShrink2(int,int,WINDOW*);

        //Getters and setters,
        int getColor() { return color; }
        int getScore() { return score; }
        char getType() { return type; }
        bool getFalling() {return falling; }
        void setFalling(bool val) { falling = val; }
        bool getNew() { return new_gem; }
        void setNew(bool var) { new_gem = var; }
    protected:
        int color;
        int score;
        char type;              //'B' for basic 'X' for undeclared
};

#endif // GEM_H
