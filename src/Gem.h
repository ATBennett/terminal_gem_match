#include <utility>
#ifndef GEM_H
#define GEM_H


class Gem
{
    private:
        int colour;
        int score;
        bool falling;
        bool newGem;
        char type;
    public:
        Gem(int,int);
        virtual ~Gem();

        void printVoid(int,int);
        void printGem(int,int);
        void printShrink1(int,int);
        void printShrink2(int,int);

        int getColour();
        int getScore();
        char getType();
        bool getFalling();
        void setFalling(bool);
        bool getIfNew();
        void setOld();
    protected:
        void setType(char);
};

#endif // GEM_H
