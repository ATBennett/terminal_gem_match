#include "../include/Gem.h"
#include <ncurses.h>

Gem::Gem(int ncolour, int nscore)
{
    newGem = true;
    colour=ncolour;
    score=nscore;
    type = 'R';
    falling = false;
}

Gem::~Gem()
{
    //dtor
}

char Gem::getType(){
    return type;
}

void Gem::setType(char nType){
    type = nType;
    return;
}
int Gem::getColour()
{
    return colour;
}

int Gem::getScore()
{
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

void Gem::printShrink1(int xloc,int yloc)
{
    attron(COLOR_PAIR(colour));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(colour));
}

void Gem::printShrink2(int xloc,int yloc)
{
    attron(COLOR_PAIR(colour));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(colour));
}

void Gem::printGem(int xloc,int yloc)
{
    attron(COLOR_PAIR(colour));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(colour));
}
