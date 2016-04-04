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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void RedGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void RedGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void GreenGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void GreenGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void YellowGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void YellowGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void BlueGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void BlueGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void MagentaGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void MagentaGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void CyanGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void CyanGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
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
    attron(COLOR_PAIR(color));
    if(yloc >= 0) mvprintw(yloc,xloc,"/    \\");
    if(yloc + 1 >= 0) mvprintw(yloc+1,xloc,"|    |");
    if(yloc + 2 >= 0) mvprintw(yloc+2,xloc,"\\    /");
    attroff(COLOR_PAIR(color));
}
void WhiteGem::printShrink1(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc,xloc+2,"  ");
    mvprintw(yloc+1,xloc,"      ");
    mvprintw(yloc+2,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}
void WhiteGem::printShrink2(int xloc,int yloc){
    attron(COLOR_PAIR(color));
    mvprintw(yloc+1,xloc+2,"  ");
    attroff(COLOR_PAIR(color));
}