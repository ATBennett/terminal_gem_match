//Implementation of the Gem superclass.

#include "../include/Gem.h"
#include "../include/definitions.h"

Gem::Gem(int color_in)
{
    new_gem = true;
    color=color_in;
    score=0;
    multiplier = 0;
    type = 'X';
    falling = false;
    activated = false;
}

Gem::~Gem()
{
    //dtor
}

//Prints a Gem sized blank space at x,y.
void Gem::printVoid(int x_loc, int y_loc, WINDOW *window1)
{
    int max_x = GEM_WIDTH*BOARD_WIDTH;
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron(window1, COLOR_PAIR(COLOR_BLACK));
    for(int x = x_loc; x < GEM_WIDTH+x_loc && x < max_x; x++)
    {
        for(int y = y_loc; y < GEM_HEIGHT+y_loc && y < max_y; y++)
        {
            mvwaddch( window1, y,x,' ');
        }
    }
    wattroff(window1, COLOR_PAIR(COLOR_BLACK));
}

//By Default a gem prints it's color in a 6x3 square.
void Gem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_x = GEM_WIDTH*BOARD_WIDTH;
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron(window1, COLOR_PAIR(color));
    for(int x = x_loc; x < GEM_WIDTH+x_loc && x < max_x; x++)
    {
        for(int y = y_loc; y < GEM_HEIGHT+y_loc && y < max_y; y++)
        {
            mvwaddch( window1, y,x,' ');
        }
    }
    wattroff(window1, COLOR_PAIR(color));
}

std::vector<std::pair<int,int> > Gem::getKillCoords(int x_loc, int y_loc){
    std::vector<std::pair<int,int> > coord_buffer;
    return coord_buffer;
}
