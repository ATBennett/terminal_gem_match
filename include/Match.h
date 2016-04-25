#ifndef MATCH_H
#define MATCH_H

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
        void printGems(WINDOW*, Gem*(*)[100][100]);
        void printShrink(int,WINDOW*, Gem*(*)[100][100]);
        void printAbsorb(int,WINDOW*, Gem*(*)[100][100]);
        void printVoid(WINDOW*, Gem*(*)[100][100]);
        void deleteGems(Gem*(*)[100][100]);
        void replaceWithSpecial(Gem*(*)[100][100]);
        void replaceWithRand(Gem*(*)[100][100]);

        //Getters and setters
        std::vector<std::pair<int,int> > getGemLocs() { return gem_locs; }
        bool getLargeMatch() { return large_match; }
};

#endif // MATCH_H
