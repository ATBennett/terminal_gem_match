//Gem superclass.

#ifndef GEM_H
#define GEM_H

#include <ncurses.h>
#include <vector>
#include "Effect.h"


class Gem
{
    private:
        bool falling;
        bool new_gem;    //Set to true on creation.
        bool activated;

    public:
        Gem(int);
        virtual ~Gem();

        void printVoid(int,int,WINDOW*);
        virtual void printGem(int,int,WINDOW*);
        virtual std::vector<std::pair<int,int> > getKillCoords(int,int); //Returns the coordinates of all the gems to be removed from matching this gem
        virtual Effect* initEffect(int,int,WINDOW*) { return nullptr; } //Returns a pointer to a new effect created by the gem

        //Getters and setters,
        int getColor() { return color; }
        int getScore() { return score; }
        float getMultiplier() { return multiplier; }
        char getType() { return type; }
        bool getFalling() {return falling; }
        void setFalling(bool val) { falling = val; }
        bool getNew() { return new_gem; }
        void setNew(bool var) { new_gem = var; }
        void setActivated(bool var) { activated = var; }
        bool getActivated() { return activated; }

    protected:
        int color;
        int score;
        float multiplier;
        char type;              //'B' for basic 'X' for undeclared
};

#endif // GEM_H
