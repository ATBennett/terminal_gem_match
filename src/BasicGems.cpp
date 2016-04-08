//Implementations of the 7 basic gems with seperate print functions

#include "../include/BasicGems.h"
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

void RedGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_RED));
    if(yloc >= 0){
        mvaddch(yloc, xloc,ACS_ULCORNER);
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        addch(ACS_URCORNER);
    }
    if(yloc + 1 >= 0){
        mvaddch(yloc+1,xloc,ACS_VLINE);
        printw("   ");
        addch(ACS_VLINE);
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2,xloc,ACS_LLCORNER);
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        addch(ACS_LRCORNER);
    }
    attroff(COLOR_PAIR(COLOR_RED));
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

void GreenGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_GREEN));
    if(yloc >= 0){
        mvaddch(yloc, xloc,'/');
        addch(A_ALTCHARSET | 111);
        addch(A_ALTCHARSET | 111);
        addch(A_ALTCHARSET | 111);
        addch('\\');
    }
    if(yloc + 1 >= 0){
        mvaddch(yloc+1,xloc,ACS_VLINE);
        printw("   ");
        addch(ACS_VLINE);
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2,xloc,'\\');
        addch(A_ALTCHARSET | 115);
        addch(A_ALTCHARSET | 115);
        addch(A_ALTCHARSET | 115);
        addch('/');
    }
    attroff(COLOR_PAIR(COLOR_GREEN));
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

void YellowGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_YELLOW));
    if(yloc >= 0){
        mvaddch(yloc, xloc,' ');
        addch('/');
        addch('^');
        addch('\\');
        addch(' ');
    }
    if(yloc + 1 >= 0){
        mvaddch(yloc+1,xloc,'(');
        printw("   ");
        addch(')');
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2, xloc,' ');
        addch('\\');
        addch('v');
        addch('/');
        addch(' ');
    }
    attroff(COLOR_PAIR(COLOR_YELLOW));
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

void BlueGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_BLUE));
    if(yloc >= 0){
        mvaddch(yloc, xloc,'/');
        addch(A_ALTCHARSET | 111);
        addch(A_ALTCHARSET | 111);
        addch(A_ALTCHARSET | 111);
        addch('\\');
    }
    if(yloc + 1 >= 0){
        mvaddch(yloc+1,xloc,'\\');
        printw("   ");
        addch('/');
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2, xloc,' ');
        addch('\\');
        addch('v');
        addch('/');
        addch(' ');
    }
    attroff(COLOR_PAIR(COLOR_BLUE));
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

void MagentaGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_MAGENTA));
    if(yloc >= 0){
        mvprintw(yloc, xloc," /^\\ ");
    }
    if(yloc + 1 >= 0){
        mvprintw(yloc+1,xloc,"/   \\");
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2,xloc,'\\');
        addch(A_ALTCHARSET | 115);
        addch(A_ALTCHARSET | 115);
        addch(A_ALTCHARSET | 115);
        addch('/');
    }
    attroff(COLOR_PAIR(COLOR_MAGENTA));
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

void CyanGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_CYAN));
    if(yloc >= 0){
        mvaddch(yloc, xloc,' ');
        addch('/');
        addch('^');
        addch('\\');
        addch(' ');
    }
    if(yloc + 1 >= 0){
        mvaddch(yloc+1,xloc,ACS_VLINE);
        printw("   ");
        addch(ACS_VLINE);
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2, xloc,' ');
        addch('\\');
        addch('v');
        addch('/');
        addch(' ');
    }
    attroff(COLOR_PAIR(COLOR_CYAN));
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

void WhiteGem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(COLOR_WHITE));
    if(yloc >= 0){
        mvaddch(yloc, xloc,' ');
        addch('/');
        addch(ACS_HLINE);
        addch('\\');
        addch(' ');
    }
    if(yloc + 1 >= 0){
        mvaddch(yloc+1,xloc,'(');
        printw("   ");
        addch(')');
    }
    if(yloc + 2 >= 0){
        mvaddch(yloc+2, xloc,' ');
        addch('\\');
        addch(ACS_HLINE);
        addch('/');
        addch(' ');
    }
    attroff(COLOR_PAIR(COLOR_WHITE));
}
