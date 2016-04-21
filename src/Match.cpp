#include "../include/Match.h"
#include "../include/definitions.h"

Match::Match(std::vector<std::pair<int,int> > gem_locs_in)
{
    gem_locs = gem_locs_in;
    type = 'R';
}

Match::~Match()
{
    //dtor
}

void Match::printShrink1(WINDOW* Window_1, Gem *Gem_Grid[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        Gem_Grid[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
        Gem_Grid[x][y]->printShrink1(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }
}

void Match::printShrink2(WINDOW* Window_1, Gem *Gem_Grid[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        Gem_Grid[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
        Gem_Grid[x][y]->printShrink2(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }
}

void Match::printVoid(WINDOW* Window_1, Gem *Gem_Grid[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        Gem_Grid[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }
}
