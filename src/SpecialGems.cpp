#include "../include/SpecialGems.h"
#include "../include/definitions.h"
#include <ncurses.h>

StarGem::StarGem(int color_in)
: Gem(color_in)
{
    type = 'S';
    score = 15;
    multiplier = 0.666666;
}

StarGem::~StarGem()
{
    //dtor
}

void StarGem::printGem(int x_loc,int y_loc,WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(color));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,' ');
        waddch( window1, '/');
        waddch( window1, ACS_CKBOARD);
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc,' ');
        waddch( window1, '\\');
        waddch( window1, ACS_CKBOARD);
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(color));
}

std::vector<std::pair<int,int> > StarGem::getKillCoords(int x_loc, int y_loc)
{
    std::vector<std::pair<int,int> > coord_buffer;
    for(int i = 0; i < BOARD_HEIGHT; i++)
        coord_buffer.push_back(std::make_pair(x_loc,i));

    for(int i = 0; i < BOARD_WIDTH; i++)
        if(i != x_loc)
            coord_buffer.push_back(std::make_pair(i,y_loc));

    return coord_buffer;
}

FireGem::FireGem(int color_in)
: Gem(color_in)
{
    type = 'S';
    score = 10;
    multiplier = 0.5;
}

FireGem::~FireGem()
{
    //dtor
}

void FireGem::printGem(int x_loc,int y_loc,WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(color));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,ACS_CKBOARD);
        waddch( window1, '/');
        waddch( window1, ACS_HLINE);
        waddch( window1, '\\');
        waddch( window1, ACS_CKBOARD);
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,ACS_CKBOARD);
        waddch( window1, ACS_VLINE);
        waddch( window1, ' ');
        waddch( window1, ACS_VLINE);
        waddch( window1, ACS_CKBOARD);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc, ACS_CKBOARD);
        waddch( window1, '\\');
        waddch( window1, ACS_HLINE);
        waddch( window1, '/');
        waddch( window1, ACS_CKBOARD);
    }
    wattroff( window1, COLOR_PAIR(color));
}

std::vector<std::pair<int,int> > FireGem::getKillCoords(int x_loc, int y_loc)
{
    std::vector<std::pair<int,int> > coord_buffer;
    coord_buffer.push_back(std::make_pair(x_loc,y_loc));
    if(x_loc > 0)
    {
        coord_buffer.push_back(std::make_pair(x_loc-1,y_loc));
        if(y_loc > 0)
            coord_buffer.push_back(std::make_pair(x_loc-1,y_loc-1));
        if(y_loc < BOARD_HEIGHT - 1)
            coord_buffer.push_back(std::make_pair(x_loc-1,y_loc+1));
    }
    if(x_loc < BOARD_WIDTH - 1)
    {
        coord_buffer.push_back(std::make_pair(x_loc+1,y_loc));
        if(y_loc > 0)
            coord_buffer.push_back(std::make_pair(x_loc+1,y_loc-1));
        if(y_loc < BOARD_HEIGHT - 1)
            coord_buffer.push_back(std::make_pair(x_loc+1,y_loc+1));
    }
    if(y_loc > 0)
        coord_buffer.push_back(std::make_pair(x_loc,y_loc-1));
    if(y_loc < BOARD_HEIGHT - 1)
        coord_buffer.push_back(std::make_pair(x_loc,y_loc+1));

    return coord_buffer;
}

ColorNukeGem::ColorNukeGem()
: Gem(COLOR_NUKE)
{
    type = 'N';
    score = 20;
    multiplier = 1;
}

ColorNukeGem::~ColorNukeGem()
{
    //dtor
}

void ColorNukeGem::printGem(int x_loc,int y_loc,WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(color));
    wattron( window1, A_BOLD);
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,ACS_ULCORNER);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_URCORNER);
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,ACS_VLINE);
        waddch( window1, ' ');
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ' ');
        waddch( window1, ACS_VLINE);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc + 2, x_loc,ACS_LLCORNER);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_LRCORNER);
    }
    wattroff( window1, COLOR_PAIR(color));
    wattroff( window1, A_BOLD);
}

StarNukeGem::StarNukeGem(int color_in)
: Gem(color_in)
{
    type = 'S';
    score = 25;
    multiplier = 1.5;
}

StarNukeGem::~StarNukeGem()
{
    //dtor
}

void StarNukeGem::printGem(int x_loc,int y_loc,WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(color));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,'/');
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, '\\');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc,'/');
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, ACS_CKBOARD);
        waddch( window1, '\\');
    }
    wattroff( window1, COLOR_PAIR(color));
}

std::vector<std::pair<int,int> > StarNukeGem::getKillCoords(int x_loc, int y_loc)
{
    std::vector<std::pair<int,int> > coord_buffer;
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        if(x_loc > 0)
            coord_buffer.push_back(std::make_pair(x_loc-1,i));

        coord_buffer.push_back(std::make_pair(x_loc,i));

        if(x_loc < BOARD_WIDTH - 1)
            coord_buffer.push_back(std::make_pair(x_loc+1,i));
    }
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        if(i != x_loc && i != x_loc - 1 && i != x_loc + 1)
        {
            if(y_loc > 0)
                coord_buffer.push_back(std::make_pair(i,y_loc - 1));

            coord_buffer.push_back(std::make_pair(i,y_loc));

            if(y_loc < BOARD_HEIGHT - 1)
                coord_buffer.push_back(std::make_pair(i,y_loc + 1));
        }
    }

    return coord_buffer;
}
