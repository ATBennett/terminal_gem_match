//Gem superclass.

#ifndef GEM_H
#define GEM_H

#include <ncurses.h>
#include <vector>


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
        void printShrink(int,int,int,WINDOW*);
        virtual std::vector<std::pair<int,int> > getKillCoords(int,int); //Returns the coordinates of all the gems to be removed from matching this gem

        //Getters and setters,
        int getColor() { return color; }
        int getScore() { return score; }
        float getMultiplier() { return multiplier; }
        char getType() { return type; }
        bool getFalling() {return falling; }
        void setFalling(bool val) { falling = val; }
        bool getNew() { return new_gem; }
        void setNew(bool var) { new_gem = var; }
    protected:
        int color;
        int score;
        float multiplier;
        char type;              //'B' for basic 'X' for undeclared
};

#endif // GEM_H
