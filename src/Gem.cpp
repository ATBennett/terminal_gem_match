//Implementation of the Gem superclass.

#include "../include/Gem.h"
#include "../include/definitions.h"

Gem::Gem()
{
    new_gem = true;
    color=COLOR_BLACK;
    score=0;
    multiplier = 0;
    type = 'X';
    falling = false;
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
//Prints a smaller version of the gem at x,y.
void Gem::printShrink1(int x_loc,int y_loc, WINDOW *window1)
{
    wattron(window1, COLOR_PAIR(color));
    mvwprintw(window1,y_loc,x_loc+2," ");
    mvwprintw(window1,y_loc+1,x_loc+1,"   ");
    mvwprintw(window1,y_loc+2,x_loc+2," ");
    wattroff(window1, COLOR_PAIR(color));
}

//Prints an even smaller version of the gem at x,y.
void Gem::printShrink2(int x_loc,int y_loc, WINDOW *window1)
{
    wattron(window1, COLOR_PAIR(color));
    mvwprintw(window1, y_loc+1,x_loc+2," ");
    wattroff(window1, COLOR_PAIR(color));
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
    coord_buffer.push_back(std::make_pair(x_loc,y_loc));
    return coord_buffer;
}
