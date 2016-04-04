#ifndef GEM_H
#define GEM_H


class Gem
{
    private:
        bool falling;
        bool newGem;
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
        bool getIfNew();
        void setOld();
    protected:
        int color;
        int score;
        char type;
};

#endif // GEM_H
