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
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron(window1, COLOR_PAIR(COLOR_BLACK));
    if(y_loc >= 0 && y_loc < max_y) mvwprintw(window1, y_loc,x_loc,"     ");
    if(y_loc + 1 >= 0 && y_loc+1 < max_y) mvwprintw(window1,y_loc+1,x_loc,"     ");
    if(y_loc + 2 >= 0 && y_loc+2 < max_y) mvwprintw(window1,y_loc+2,x_loc,"     ");
    wattroff(window1, COLOR_PAIR(COLOR_BLACK));
}

//By Default a gem prints it's color in a 6x3 square.
void Gem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron(window1, COLOR_PAIR(color));
    if(y_loc >= 0 && y_loc < max_y) mvwprintw( window1, y_loc,x_loc,"     ");
    if(y_loc + 1 >= 0 && y_loc+1 < max_y) mvwprintw( window1, y_loc+1,x_loc,"     ");
    if(y_loc + 2 >= 0 && y_loc+2 < max_y) mvwprintw( window1, y_loc+2,x_loc,"     ");
    wattroff(window1, COLOR_PAIR(color));
}

std::vector<std::pair<int,int> > Gem::getKillCoords(int x_loc, int y_loc){
    std::vector<std::pair<int,int> > coord_buffer;
    return coord_buffer;
}
