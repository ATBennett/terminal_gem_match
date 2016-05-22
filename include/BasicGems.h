//This Header file declares the seperate classes for the basic gems.
//Each gem class overwrites the print functions,so they can all be displayed differently.
#ifndef BASICGEMS_H
#define BASICGEMS_H

#include "Gem.h"
#include <ncurses.h>


class RedGem: public Gem
{
    public:
        RedGem();
        virtual ~RedGem();
        void printGem(int,int, WINDOW*) override;
};

class GreenGem: public Gem
{
    public:
        GreenGem();
        virtual ~GreenGem();
        void printGem(int,int, WINDOW*) override;
};

class YellowGem: public Gem
{
    public:
        YellowGem();
        virtual ~YellowGem();
        void printGem(int,int, WINDOW*) override;
};

class BlueGem: public Gem
{
    public:
        BlueGem();
        virtual ~BlueGem();
        void printGem(int,int, WINDOW*) override;
};

class MagentaGem: public Gem
{
    public:
        MagentaGem();
        virtual ~MagentaGem();
        void printGem(int,int, WINDOW*) override;
};

class CyanGem: public Gem
{
    public:
        CyanGem();
        virtual ~CyanGem();
        void printGem(int,int, WINDOW*) override;
};

class WhiteGem: public Gem
{
    public:
        WhiteGem();
        virtual ~WhiteGem();
        void printGem(int,int, WINDOW*) override;
};

#endif // BASICGEMS_H
