//Gem superclass

#ifndef GEM_H
#define GEM_H


class Gem
{
    private:
        bool falling;
        bool newGem;    //set to true on creation
    public:
        Gem();
        virtual ~Gem();

        void printVoid(int,int);
        virtual void printGem(int,int);
        virtual void printShrink1(int,int);
        virtual void printShrink2(int,int);

        //gets and sets
        int getColor() { return color; }
        int getScore() { return score; }
        char getType() { return type; }
        bool getFalling() {return falling; }
        void setFalling(bool val) { falling = val; }
        bool getNew() { return newGem; }        //returns value of newGem
        void setOld() { newGem = false; }          //sets newGem to false
    protected:
        int color;
        int score;
        char type;              //'B' for basic 'X' for undeclared
};

#endif // GEM_H
