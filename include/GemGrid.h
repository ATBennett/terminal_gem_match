//This class manages everything on the GemGrid.

#ifndef GEMGRID_H
#define GEMGRID_H

#include "BasicGems.h"
#include "Match.h"
#include "cfg.h"
#include <vector>
#include <string>



class GemGrid
{
    private:
        //2D matrix of gems in format y,x
        std::vector<std::vector<Gem*> > Gem_Matrix;
        Gem* randGem();

        //Causes gems to fall down by 1.
        void fallGems();
        int swapGemPosition(unsigned int,unsigned int,unsigned int,unsigned int);
        std::vector<Match> color_nuke(int,int,int,int);
        std::vector<std::pair<unsigned int,unsigned int> > matchV(unsigned int,unsigned int);
        std::vector<std::pair<unsigned int,unsigned int> > matchH(unsigned int,unsigned int);
        std::vector<Match> intersectMatches(std::vector<Match>);

        WINDOW* Window_1;
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
        float swapGems(unsigned int,unsigned int,char);
        void fallAll();
        void printCursor(int,int,char);
        void removeCursor(int,int);

        //Getters and setters,
        WINDOW* getWindow() { return Window_1; }
};

#endif // GEMGRID_H
