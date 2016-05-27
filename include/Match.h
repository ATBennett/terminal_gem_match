#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <ncurses.h>
#include "Gem.h"
#include "cfg.h"


class Match
{
    private:
        std::vector<std::pair<unsigned int,unsigned int> > gem_locs;
        bool large_match;
        bool intersecting;
        int length_of_match;
        std::pair<unsigned int,unsigned int> start_loc;

        Gem* randGem();
        Gem* createRegularGem(int);

    protected:
    public:
        Match(std::vector<std::pair<unsigned int,unsigned int> >);
        Match(std::vector<std::pair<unsigned int,unsigned int> >, bool);
        virtual ~Match();

        //Operations for a match to work on a grid via a pointer to the grid
        void printGems(WINDOW*, std::vector<std::vector<Gem*> >(&));
        void printAbsorb(int,WINDOW*, std::vector<std::vector<Gem*> >(&));
        void printVoid(WINDOW*, std::vector<std::vector<Gem*> >(&));
        float deleteGems(std::vector<std::vector<Gem*> >(&));
        float replaceWithSpecial(std::vector<std::vector<Gem*> >(&));
        void replaceWithRand(std::vector<std::vector<Gem*> >(&));

        //Getters and setters
        std::vector<std::pair<unsigned int,unsigned int> > getGemLocs() { return gem_locs; }
        bool getLargeMatch() { return large_match; }
};

#endif // MATCH_H
