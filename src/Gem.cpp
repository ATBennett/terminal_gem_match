//Implementation of the Gem superclass

#include "../include/Gem.h"
#include <ncurses.h>

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
void Gem::printVoid(int xloc, int yloc){
    attron(COLOR_PAIR(COLOR_BLACK));
    mvprintw(yloc,xloc,"     ");
    mvprintw(yloc+1,xloc,"     ");
    mvprintw(yloc+2,xloc,"     ");
    attroff(COLOR_PAIR(COLOR_BLACK));
}
// Prints a smaller version of the gem at x,y
void Gem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+1,"   ");
    mvprintw(yloc+1,xloc,"     ");
    mvprintw(yloc+2,xloc+1,"   ");
    attroff(COLOR_PAIR(color));
}

// Prints an even smaller version of the gem at x,y
void Gem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2," ");
    attroff(COLOR_PAIR(color));
}
// By Default a gem prints it's color in a 6x3 square
void Gem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"     ");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"     ");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"     ");
    attroff(COLOR_PAIR(color));
}
