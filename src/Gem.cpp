//Implementation of the Gem superclass

#include "../include/Gem.h"
#include "../include/definitions.h"

Gem::Gem(){
    newGem = true;
    color=COLOR_BLACK;
    score=0;
    type = 'X';
    falling = false;
}

Gem::~Gem(){
    //dtor
}

// Prints a Gem sized blank space at x,y
void Gem::printVoid(int xloc, int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron(window1, COLOR_PAIR(COLOR_BLACK));
    if(yloc >= 0 && yloc < maxY) mvwprintw(window1, yloc,xloc,"     ");
    if(yloc + 1 >= 0 && yloc+1 < maxY) mvwprintw(window1,yloc+1,xloc,"     ");
    if(yloc + 2 >= 0 && yloc+2 < maxY) mvwprintw(window1,yloc+2,xloc,"     ");
    wattroff(window1, COLOR_PAIR(COLOR_BLACK));
}
// Prints a smaller version of the gem at x,y
void Gem::printShrink1(int xloc,int yloc, WINDOW *window1){
    wattron(window1, COLOR_PAIR(color));
    mvwprintw(window1,yloc,xloc+2," ");
    mvwprintw(window1,yloc+1,xloc+1,"   ");
    mvwprintw(window1,yloc+2,xloc+2," ");
    wattroff(window1, COLOR_PAIR(color));
}

// Prints an even smaller version of the gem at x,y
void Gem::printShrink2(int xloc,int yloc, WINDOW *window1){
    wattron(window1, COLOR_PAIR(color));
    mvwprintw(window1, yloc+1,xloc+2," ");
    wattroff(window1, COLOR_PAIR(color));
}

// By Default a gem prints it's color in a 6x3 square
void Gem::printGem(int xloc,int yloc, WINDOW *window1){
    int maxY = GemHeight*BoardHeight;
    wattron(window1, COLOR_PAIR(color));
    if(yloc >= 0 && yloc < maxY) mvwprintw( window1, yloc,xloc,"     ");
    if(yloc + 1 >= 0 && yloc+1 < maxY) mvwprintw( window1, yloc+1,xloc,"     ");
    if(yloc + 2 >= 0 && yloc+2 < maxY) mvwprintw( window1, yloc+2,xloc,"     ");
    wattroff(window1, COLOR_PAIR(color));
}
