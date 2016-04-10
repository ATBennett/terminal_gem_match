//Implementations of the 7 basic gems with seperate print functions

#include "../include/BasicGems.h"
#include "../include/definitions.h"
#include <ncurses.h>

RedGem::RedGem()
: Gem(){
    color = COLOR_RED;
    score = 5;
    type = 'B';
}

RedGem::~RedGem(){
    //dtor
}

void RedGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_RED));
    if(yloc >= 0 && yloc < maxY){
        mvwaddch(window1, yloc, xloc,ACS_ULCORNER);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_URCORNER);
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwaddch(window1, yloc+1,xloc,ACS_VLINE);
        wprintw( window1, "   ");
        waddch( window1, ACS_VLINE);
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2,xloc,ACS_LLCORNER);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_HLINE);
        waddch( window1, ACS_LRCORNER);
    }
    wattroff( window1, COLOR_PAIR(COLOR_RED));
}

GreenGem::GreenGem()
: Gem(){
    color = COLOR_GREEN;
    score = 5;
    type = 'B';
}

GreenGem::~GreenGem(){
    //dtor
}

void GreenGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_GREEN));
    if(yloc >= 0 && yloc < maxY){
        mvwaddch(window1, yloc, xloc,'/');
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, '\\');
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwaddch(window1, yloc+1,xloc,ACS_VLINE);
        wprintw( window1, "   ");
        waddch( window1, ACS_VLINE);
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2,xloc,'\\');
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, '/');
    }
    wattroff( window1, COLOR_PAIR(COLOR_GREEN));
}

YellowGem::YellowGem()
: Gem(){
    color = COLOR_YELLOW;
    score = 5;
    type = 'B';
}

YellowGem::~YellowGem(){
    //dtor
}

void YellowGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_YELLOW));
    if(yloc >= 0 && yloc < maxY){
        mvwaddch(window1, yloc, xloc,' ');
        waddch( window1, '/');
        waddch( window1, '^');
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwaddch(window1, yloc+1,xloc,'(');
        wprintw( window1, "   ");
        waddch( window1, ')');
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2, xloc,' ');
        waddch( window1, '\\');
        waddch( window1, 'v');
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_YELLOW));
}

BlueGem::BlueGem()
: Gem(){
    color = COLOR_BLUE;
    score = 5;
    type = 'B';
}

BlueGem::~BlueGem(){
    //dtor
}

void BlueGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_BLUE));
    if(yloc >= 0 && yloc < maxY){
        mvwaddch(window1, yloc, xloc,'/');
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, A_ALTCHARSET | 111);
        waddch( window1, '\\');
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwaddch(window1, yloc+1,xloc,'\\');
        wprintw( window1, "   ");
        waddch( window1, '/');
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2, xloc,' ');
        waddch( window1, '\\');
        waddch( window1, 'v');
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_BLUE));
}

MagentaGem::MagentaGem()
: Gem(){
    color = COLOR_MAGENTA;
    score = 5;
    type = 'B';
}

MagentaGem::~MagentaGem(){
    //dtor
}

void MagentaGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_MAGENTA));
    if(yloc >= 0 && yloc < maxY){
        mvwprintw( window1, yloc, xloc," /^\\ ");
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwprintw( window1, yloc+1,xloc,"/   \\");
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2,xloc,'\\');
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, A_ALTCHARSET | 115);
        waddch( window1, '/');
    }
    wattroff( window1, COLOR_PAIR(COLOR_MAGENTA));
}

CyanGem::CyanGem()
: Gem(){
    color = COLOR_CYAN;
    score = 5;
    type = 'B';
}

CyanGem::~CyanGem(){
    //dtor
}

void CyanGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_CYAN));
    if(yloc >= 0 && yloc < maxY){
        mvwaddch(window1, yloc, xloc,' ');
        waddch( window1, '/');
        waddch( window1, '^');
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwaddch(window1, yloc+1,xloc,ACS_VLINE);
        wprintw( window1, "   ");
        waddch( window1, ACS_VLINE);
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2, xloc,' ');
        waddch( window1, '\\');
        waddch( window1, 'v');
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_CYAN));
}

WhiteGem::WhiteGem()
: Gem(){
    color = COLOR_WHITE;
    score = 5;
    type = 'B';
}

WhiteGem::~WhiteGem(){
    //dtor
}

void WhiteGem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron( window1, COLOR_PAIR(COLOR_WHITE));
    if(yloc >= 0 && yloc < maxY){
        mvwaddch(window1, yloc, xloc,' ');
        waddch( window1, '/');
        waddch( window1, ACS_HLINE);
        waddch( window1, '\\');
        waddch( window1, ' ');
    }
    if(yloc + 1 >= 0 && yloc + 1 < maxY){
        mvwaddch(window1, yloc+1,xloc,'(');
        wprintw( window1, "   ");
        waddch( window1, ')');
    }
    if(yloc + 2 >= 0 && yloc + 2 < maxY){
        mvwaddch(window1, yloc+2, xloc,' ');
        waddch( window1, '\\');
        waddch( window1, ACS_HLINE);
        waddch( window1, '/');
        waddch( window1, ' ');
    }
    wattroff( window1, COLOR_PAIR(COLOR_WHITE));
}
