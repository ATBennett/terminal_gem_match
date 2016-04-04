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

char Gem::getType(){
    return type;
}

int Gem::getColor(){
    return color;
}

int Gem::getScore(){
    return score;
}

void Gem::setFalling(bool nFalling){
    falling = nFalling;
    return;
}

bool Gem::getFalling(){
    return falling;
}

bool Gem::getIfNew(){
    return newGem;
}

void Gem::setOld(){
    newGem = false;
    return;
}

void Gem::printVoid(int xloc, int yloc){
    attron(COLOR_PAIR(COLOR_BLACK));
    mvprintw(yloc,xloc,"      ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc,"      ");
    attroff(COLOR_PAIR(COLOR_BLACK));
}

void Gem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}

void Gem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}

void Gem::printGem(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
