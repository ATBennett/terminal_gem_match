#include "../include/Match.h"
#include "../include/definitions.h"
#include "../include/BasicGems.h"
#include "../include/SpecialGems.h"

#include <algorithm>

Match::Match(std::vector<std::pair<int,int> > gem_locs_in)
{
    gem_locs = gem_locs_in;
    large_match = false; //Default value for 'Regular' match.
    intersecting = false;

    if(gem_locs.size() > 3)
        large_match = true; //'A' for 'Absorbing' match.

    std::sort(gem_locs.begin(),gem_locs.end());
    start_loc = gem_locs[0];

    for(unsigned int i = 1; i < gem_locs.size(); i++)
    {
        if(gem_locs[i] == gem_locs[i-1])
        {
            intersecting = true;
            start_loc = gem_locs[i];
            gem_locs.erase(gem_locs.begin() + i);
            break;
        }
    }

    length_of_match = gem_locs.size();
}

Match::Match(std::vector<std::pair<int,int> > gem_locs_in, bool quick_destroy)
{
    gem_locs = gem_locs_in;
    intersecting = false;
    large_match = false;

    if(gem_locs.size() > 3 && !quick_destroy)
        large_match = true; //'A' for 'Absorbing' match.

    std::sort(gem_locs.begin(),gem_locs.end());
    start_loc = gem_locs[0];

    for(unsigned int i = 1; i < gem_locs.size(); i++)
    {
        if(gem_locs[i] == gem_locs[i-1])
        {
            intersecting = true;
            start_loc = gem_locs[i];
            gem_locs.erase(gem_locs.begin() + i);
            break;
        }
    }

    length_of_match = gem_locs.size();
}

Match::~Match()
{
    //dtor
}

void Match::printShrink(int shrink,WINDOW* Window_1, Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
        {
            Gem_Grid[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
            Gem_Grid[x][y]->printShrink(shrink,x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
        }
    }
}

void Match::printAbsorb(int num,WINDOW* Window_1, Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
            Gem_Grid[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }

    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
        {
            int diff_x = (gem_locs[i].first - start_loc.first) * GEM_WIDTH;
            int diff_y = (gem_locs[i].second - start_loc.second) * GEM_HEIGHT;
            int move_x = -(diff_x/ANIM_LENGTH) * (num + 1);
            int move_y = -(diff_y/ANIM_LENGTH) * (num + 1);
            Gem_Grid[x][y]->printGem(x*GEM_WIDTH + move_x,y*GEM_HEIGHT + move_y,Window_1);
        }
    }
}

void Match::printVoid(WINDOW* Window_1, Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
            Gem_Grid[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
    }
}

float Match::deleteGems(Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    float score = 0;
    float multiplier = 0;
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
        {
            score += Gem_Grid[x][y]->getScore();
            multiplier += Gem_Grid[x][y]->getMultiplier();
            delete Gem_Grid[x][y];
            Gem_Grid[x][y]=nullptr;
        }
    }
    return score*multiplier;
}

void Match::replaceWithRand(Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
            delete Gem_Grid[x][y];
        Gem_Grid[x][y]=randGem();
    }
}

float Match::replaceWithSpecial(Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    float score = 0;
    float multiplier = 0;
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if(Gem_Grid[x][y] != nullptr)
        {
            score += Gem_Grid[x][y]->getScore();
            multiplier += Gem_Grid[x][y]->getMultiplier();
        }
        if(gem_locs[i] == start_loc)
        {
            int color = COLOR_BLACK;
            if(Gem_Grid[x][y] != nullptr)
            {
                color = Gem_Grid[x][y]->getColor();
                delete Gem_Grid[x][y];
            }

            if(intersecting)
                Gem_Grid[x][y] = new StarGem(color);

            else if(length_of_match == 4)
                Gem_Grid[x][y] = new FireGem(color);

            else if(length_of_match == 5)
                Gem_Grid[x][y] = new ColorNukeGem();

            else if(length_of_match >= 6)
                Gem_Grid[x][y] = new StarNukeGem(color);

            else
                Gem_Grid[x][y] = createRegularGem(color);

            Gem_Grid[x][y]->setNew(false);
        }
        else
        {
            if(Gem_Grid[x][y] != nullptr)
            {
                delete Gem_Grid[x][y];
                Gem_Grid[x][y]=nullptr;
            }
        }
    }
    return score*multiplier;
}

void Match::printGems(WINDOW* Window_1,Gem* (&Gem_Grid)[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT])
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        if (Gem_Grid[x][y] != nullptr)
            Gem_Grid[x][y]->printGem(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
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
        default : return nullptr;
    }
}

Gem* Match::createRegularGem(int color)
{
    switch(color)
    {
        case COLOR_RED : return new RedGem();
        case COLOR_GREEN : return new GreenGem();
        case COLOR_YELLOW : return new YellowGem();
        case COLOR_BLUE : return new BlueGem();
        case COLOR_MAGENTA : return new MagentaGem();
        case COLOR_CYAN : return new CyanGem();
        case COLOR_WHITE : return new WhiteGem();
        default : return nullptr;
    }
}
