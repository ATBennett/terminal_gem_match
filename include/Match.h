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
        void printGems(WINDOW*, Gem*(&)[32][32]);
        void printShrink(int,WINDOW*, Gem*(&)[32][32]);
        void printAbsorb(int,WINDOW*, Gem*(&)[32][32]);
        void printVoid(WINDOW*, Gem*(&)[32][32]);
        float deleteGems(Gem*(&)[32][32]);
        float replaceWithSpecial(Gem*(&)[32][32]);
        void replaceWithRand(Gem*(&)[32][32]);

        //Getters and setters
        std::vector<std::pair<int,int> > getGemLocs() { return gem_locs; }
        bool getLargeMatch() { return large_match; }
};

#endif // MATCH_H
