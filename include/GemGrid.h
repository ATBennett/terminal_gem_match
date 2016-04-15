//This class manages everything on the GemGrid.

#include "BasicGems.h"
#include "definitions.h"
#include <vector>

#ifndef GEMGRID_H
#define GEMGRID_H


class GemGrid
{
    private:
        //2D matrix of gems x,y
        Gem *Gem_Matrix[100][100];

        Gem* randGem();
        //Causes gems to fall down by 1.
        void fallGems();
        void createSpecial(std::vector<std::pair<int,int> >);

        //Not implemented yet.
        void matchL(int,int);
        void match4H(int,int);
        void match4V(int,int);
        void match5H(int,int);
        void match5V(int,int);
        void match6H(int,int);
        void match6V(int,int);

        WINDOW *Window_1;
        int grid_width;
        int grid_height;
    public:
        GemGrid(unsigned int, unsigned int, WINDOW*);
        virtual ~GemGrid();

        void createRandomGrid();
        void fallOntoBoard();
        void printGrid();
        std::vector<std::pair<int,int> > matched();     //Returns a vector of coordinates
        float fancyRemoveMatched(std::vector<std::pair<int,int> >);
        void quickRemoveMatched(std::vector<std::pair<int,int> >);
        bool swapGems(std::pair<int,int>,char);
        void fallAll();

        //Getters and setters,
        WINDOW* getWindow() { return Window_1; }
};

#endif // GEMGRID_H
