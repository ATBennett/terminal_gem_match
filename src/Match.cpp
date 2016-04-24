#include "../include/Match.h"
#include "../include/definitions.h"
#include "../include/BasicGems.h"
#include "../include/SpecialGems.h"

#include <algorithm>

Match::Match(std::vector<std::pair<int,int> > gem_locs_in)
{
    gem_locs = gem_locs_in;
    type = 'R'; //Default value for 'Regular' match.

    if(gem_locs.size() > 3)
        type = 'A'; //'A' for 'Absorbing' match.

    std::sort(gem_locs.begin(),gem_locs.end());
    start_loc = gem_locs[0];

    for(unsigned int i = 1; i < gem_locs.size(); i++)
    {
        if(gem_locs[i] == gem_locs[i-1])
        {
            start_loc = gem_locs[i];
            gem_locs.erase(gem_locs.begin() + i);
            break;
        }
    }
}

Match::Match(std::vector<std::pair<int,int> > gem_locs_in, char type_in)
{
    gem_locs = gem_locs_in;
    type = type_in; //Default value for 'Regular' match.

    std::sort(gem_locs.begin(),gem_locs.end());
    start_loc = gem_locs[0];

    for(unsigned int i = 1; i < gem_locs.size(); i++)
    {
        if(gem_locs[i] == gem_locs[i-1])
        {
            start_loc = gem_locs[i];
            gem_locs.erase(gem_locs.begin() + i);
            break;
        }
    }
}

Match::~Match()
{
    //dtor
}

void Match::printShrink(int shrink,WINDOW* Window_1, Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        (*Gem_Grid)[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
        (*Gem_Grid)[x][y]->printShrink(shrink,x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }
}

void Match::printAbsorb(int num,WINDOW* Window_1, Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        (*Gem_Grid)[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }

    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        int diff_x = (gem_locs[i].first - start_loc.first) * GEM_WIDTH;
        int diff_y = (gem_locs[i].second - start_loc.second) * GEM_HEIGHT;
        int move_x = -(diff_x/SHRINK_ANIM_LENGTH) * (num + 1);
        int move_y = -(diff_y/SHRINK_ANIM_LENGTH) * (num + 1);
        (*Gem_Grid)[x][y]->printGem(x*GEM_WIDTH + move_x,y*GEM_HEIGHT + move_y,Window_1);
    }
}

void Match::printVoid(WINDOW* Window_1, Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        (*Gem_Grid)[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }
}

void Match::deleteGems(Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        delete(*Gem_Grid)[x][y];
        (*Gem_Grid)[x][y]=NULL;
    }
}

void Match::replaceWithRand(Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        delete(*Gem_Grid)[x][y];
        (*Gem_Grid)[x][y]=randGem();
    }
}

void Match::replaceWithSpecial(Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(gem_locs[i] == start_loc)
        {

        }
        else
        {
            delete(*Gem_Grid)[x][y];
            (*Gem_Grid)[x][y]=NULL;
        }
    }
}

void Match::printGems(WINDOW* Window_1,Gem *(*Gem_Grid)[100][100])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if((*Gem_Grid)[x][y] != NULL)
            (*Gem_Grid)[x][y]->printGem(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
        else
        {
            Gem* GemBuffer = randGem();
            GemBuffer->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
            delete GemBuffer;
        }
    }
}

Gem* Match::randGem()
{
    int rand_num = rand() % 7;
    switch(rand_num)
    {
        case 0 : return new RedGem();
        case 1 : return new GreenGem();
        case 2 : return new YellowGem();
        case 3 : return new BlueGem();
        case 4 : return new MagentaGem();
        case 5 : return new CyanGem();
        case 6 : return new WhiteGem();
        default : return NULL;
    }
}
