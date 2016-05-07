//This class manages everything on the GemGrid.

#include "BasicGems.h"
#include "definitions.h"
#include "Match.h"
#include <vector>
#include <string>

#ifndef GEMGRID_H
#define GEMGRID_H


class GemGrid
{
    private:
        //2D matrix of gems x,y
        Gem* Gem_Matrix[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT];
        Gem* randGem();

        //Causes gems to fall down by 1.
        void fallGems();
        int swapGemPosition(int,int,int,int);
        std::vector<Match> color_nuke(int,int,int,int);
        std::vector<std::pair<int,int> > matchV(int,int);
        std::vector<std::pair<int,int> > matchH(int,int);
        std::vector<Match> intersectMatches(std::vector<Match>);

        WINDOW* Window_1;
        int grid_width;
        int grid_height;
    public:
        GemGrid(unsigned int, unsigned int, WINDOW*);
        virtual ~GemGrid();

        void createRandomGrid();
        void fallOntoBoard();
        void printGrid();
        std::vector<Match> getMatched();     //Returns a vector of coordinates
        std::vector<Match> fireSpecials(std::vector<Match>);
        float removeMatches(std::vector<Match>); //Returns the score from the removed gems
        void quickRemoveMatches(std::vector<Match>);
        float swapGems(int,int,char);
        void fallAll();
        void printCursor(int,int,const char*);
        void removeCursor(int,int);

        //Getters and setters,
        WINDOW* getWindow() { return Window_1; }
};

#endif // GEMGRID_H
