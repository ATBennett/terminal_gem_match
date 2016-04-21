#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <ncurses.h>
#include "Gem.h"


class Match
{
    private:
        std::vector<std::pair<int,int> > gem_locs;
        char type;
    protected:
    public:
        Match(std::vector<std::pair<int,int> >);
        virtual ~Match();

        void printShrink1(WINDOW*, Gem*[100][100]);
        void printShrink2(WINDOW*, Gem*[100][100]);
        void printVoid(WINDOW*, Gem*[100][100]);

        //Getters and setters
        std::vector<std::pair<int,int> > getGemLocs() { return gem_locs; }
        char getType() { return type; }
};

#endif // MATCH_H
