//This class manages everything on the GemGrid

#include "BasicGems.h"
#include "definitions.h"
#include <vector>

#ifndef GEMGRID_H
#define GEMGRID_H


class GemGrid
{
    private:
        Gem *GemMatrix[100][100];

        Gem* RandGem();
        void fallGems();
        void createSpecial(std::vector<std::pair<int,int> >);

        //Not implemented yet
        void matchL(int,int);
        void match4H(int,int);
        void match4V(int,int);
        void match5H(int,int);
        void match5V(int,int);
        void match6H(int,int);
        void match6V(int,int);

        WINDOW *window1;
        int gridWidth;
        int gridHeight;
    public:
        GemGrid(unsigned int, unsigned int, WINDOW*);
        virtual ~GemGrid();

        void printGrid();
        std::vector<std::pair<int,int> > matched();
        float fancyRemoveMatched(std::vector<std::pair<int,int> >);
        void quickRemoveMatched(std::vector<std::pair<int,int> >);
        bool swapGems(std::pair<int,int>,char);
        void fallAll();

        //getters and setters
        WINDOW* getWindow() { return window1; }
};

#endif // GEMGRID_H
