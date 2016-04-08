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

        int getColor();
        int getScore();
        char getType();
        bool getFalling();
        void setFalling(bool);
        bool getIfNew();        //returns value of newGem
        void setOld();          //sets newGem to false
    protected:
        int color;
        int score;
        char type;              //'B' for basic 'X' for undeclared
};

#endif // GEM_H
