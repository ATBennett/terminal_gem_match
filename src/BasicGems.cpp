//Implementations of the 7 basic gems with seperate print functions.

#include "../include/BasicGems.h"
#include "../include/definitions.h"
#include <ncurses.h>

RedGem::RedGem()
: Gem()
{
    color = COLOR_RED;
    score = 5;
    type = 'B';
}

RedGem::~RedGem()
{
    //dtor
}

void RedGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_RED));
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
        wprintw( window1, "   ");
        waddch( window1, ACS_VLINE);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2,x_loc,ACS_LLCORNER);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_LRCORNER);
    }
    wattroff( window1, COLOR_PAIR(COLOR_RED));
}

GreenGem::GreenGem()
: Gem()
{
    color = COLOR_GREEN;
    score = 5;
    type = 'B';
}

GreenGem::~GreenGem()
{
    //dtor
}

void GreenGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_GREEN));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,'/');
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, '\\');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,ACS_VLINE);
        wprintw( window1, "   ");
        waddch( window1, ACS_VLINE);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2,x_loc,'\\');
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, '/');
    }
    wattroff( window1, COLOR_PAIR(COLOR_GREEN));
}

YellowGem::YellowGem()
: Gem()
{
    color = COLOR_YELLOW;
    score = 5;
    type = 'B';
}

YellowGem::~YellowGem()
{
    //dtor
}

void YellowGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_YELLOW));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,' ');
        waddch( window1, '/');
        waddch( window1, '^');
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,'(');
        wprintw( window1, "   ");
        waddch( window1, ')');
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc,' ');
        waddch( window1, '\\');
        waddch( window1, 'v');
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_YELLOW));
}

BlueGem::BlueGem()
: Gem()
{
    color = COLOR_BLUE;
    score = 5;
    type = 'B';
}

BlueGem::~BlueGem()
{
    //dtor
}

void BlueGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_BLUE));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,'/');
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, '\\');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,'\\');
        wprintw( window1, "   ");
        waddch( window1, '/');
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc,' ');
        waddch( window1, '\\');
        waddch( window1, 'v');
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_BLUE));
}

MagentaGem::MagentaGem()
: Gem()
{
    color = COLOR_MAGENTA;
    score = 5;
    type = 'B';
}

MagentaGem::~MagentaGem()
{
    //dtor
}

void MagentaGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_MAGENTA));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwprintw( window1, y_loc, x_loc," /^\\ ");
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwprintw( window1, y_loc+1,x_loc,"/   \\");
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2,x_loc,'\\');
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, '/');
    }
    wattroff( window1, COLOR_PAIR(COLOR_MAGENTA));
}

CyanGem::CyanGem()
: Gem()
{
    color = COLOR_CYAN;
    score = 5;
    type = 'B';
}

CyanGem::~CyanGem()
{
    //dtor
}

void CyanGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_CYAN));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,' ');
        waddch( window1, '/');
        waddch( window1, '^');
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,ACS_VLINE);
        wprintw( window1, "   ");
        waddch( window1, ACS_VLINE);
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc,' ');
        waddch( window1, '\\');
        waddch( window1, 'v');
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_CYAN));
}

WhiteGem::WhiteGem()
: Gem()
{
    color = COLOR_WHITE;
    score = 5;
    type = 'B';
}

WhiteGem::~WhiteGem()
{
    //dtor
}

void WhiteGem::printGem(int x_loc,int y_loc, WINDOW *window1)
{
    int max_y = GEM_HEIGHT*BOARD_HEIGHT;
    wattron( window1, COLOR_PAIR(COLOR_WHITE));
    if(y_loc >= 0 && y_loc < max_y)
    {
        mvwaddch(window1, y_loc, x_loc,' ');
        waddch( window1, '/');
        waddch( window1, ACS_HLINE);
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(y_loc + 1 >= 0 && y_loc + 1 < max_y)
    {
        mvwaddch(window1, y_loc+1,x_loc,'(');
        wprintw( window1, "   ");
        waddch( window1, ')');
    }
    if(y_loc + 2 >= 0 && y_loc + 2 < max_y)
    {
        mvwaddch(window1, y_loc+2, x_loc,' ');
        waddch( window1, '\\');
        waddch( window1, ACS_HLINE);
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_WHITE));
}
