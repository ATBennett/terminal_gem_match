#ifndef MATCH_H
#define MATCH_H

#include "definitions.h"
#include <vector>
#include <ncurses.h>
#include "Gem.h"


class Match
{
    private:
        std::vector<std::pair<int,int> > gem_locs;
        bool large_match;
        bool intersecting;
        int length_of_match;
        std::pair<int,int> start_loc;

        Gem* randGem();
        Gem* createRegularGem(int);

    protected:
    public:
        Match(std::vector<std::pair<int,int> >);
        Match(std::vector<std::pair<int,int> >, bool);
        virtual ~Match();

        //Operations for a match to work on a grid via a pointer to the grid
        void printGems(WINDOW*, Gem*(&)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT]);
        void printAbsorb(int,WINDOW*, Gem*(&)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT]);
        void printVoid(WINDOW*, Gem*(&)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT]);
        float deleteGems(Gem*(&)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT]);
        float replaceWithSpecial(Gem*(&)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT]);
        void replaceWithRand(Gem*(&)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT]);

        //Getters and setters
        std::vector<std::pair<int,int> > getGemLocs() { return gem_locs; }
        bool getLargeMatch() { return large_match; }
};

#endif // MATCH_H
