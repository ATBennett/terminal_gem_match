//This class manages everything on the GemGrid.

#include "BasicGems.h"
#include "definitions.h"
#include "Match.h"
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
        int swapGemPosition(int,int,int,int);
        std::vector<Match> color_nuke(int,int,int,int);
        std::vector<std::pair<int,int> > matchXY(int,int);

        WINDOW *Window_1;
        int grid_width;
        int grid_height;
    public:
        GemGrid(unsigned int, unsigned int, WINDOW*);
        virtual ~GemGrid();

        void createRandomGrid();
        void fallOntoBoard();
        void printGrid();
        std::vector<Match> getMatched();     //Returns a vector of coordinates
        float fireSpecials(std::vector<Match>); // Recursively finds all the gems that have been killed
        float removeMatches(std::vector<Match>); //Returns the score from the removed gems
        void quickRemoveMatches(std::vector<Match>);
        float swapGems(int,int,char);
        void fallAll();

        //Getters and setters,
        WINDOW* getWindow() { return Window_1; }
};

#endif // GEMGRID_H
