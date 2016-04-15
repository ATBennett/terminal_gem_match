//This Header file declares the seperate classes for the basic gems.
//Each gem class overwrites the print functions,so they can all be displayed differently.

#include "Gem.h"
#include <ncurses.h>
#ifndef BASICGEMS_H
#define BASICGEMS_H

class RedGem: public Gem
{
    public:
        RedGem();
        virtual ~RedGem();
        void printGem(int,int, WINDOW*);
};

class GreenGem: public Gem
{
    public:
        GreenGem();
        virtual ~GreenGem();
        void printGem(int,int, WINDOW*);
};

class YellowGem: public Gem
{
    public:
        YellowGem();
        virtual ~YellowGem();
        void printGem(int,int, WINDOW*);
};

class BlueGem: public Gem
{
    public:
        BlueGem();
        virtual ~BlueGem();
        void printGem(int,int, WINDOW*);
};

class MagentaGem: public Gem
{
    public:
        MagentaGem();
        virtual ~MagentaGem();
        void printGem(int,int, WINDOW*);
};

class CyanGem: public Gem
{
    public:
        CyanGem();
        virtual ~CyanGem();
        void printGem(int,int, WINDOW*);
};

class WhiteGem: public Gem
{
    public:
        WhiteGem();
        virtual ~WhiteGem();
        void printGem(int,int, WINDOW*);
};

#endif // BASICGEMS_H
