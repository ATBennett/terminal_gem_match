#include "../include/ShrinkEffect.h"

ShrinkEffect::ShrinkEffect(int x_loc, int y_loc, int length, WINDOW* Window_1)
: Effect( x_loc, y_loc, length, Window_1 )
{
    //ctor
}

ShrinkEffect::~ShrinkEffect()
{
    //dtor
}

void ShrinkEffect::playEffect()
{
    cycle++;
    switch(cycle)
    {
        case 1:
            attron(COLOR_PAIR(COLOR_BLACK));
            mvwprintw(Window_1,y_location,x_location," ");                      //.000.
            mvwprintw(Window_1,y_location,x_location+GEM_WIDTH - 1," ");        //00000
            mvwprintw(Window_1,y_location + 2,x_location," ");                  //.000.
            mvwprintw(Window_1,y_location + 2,x_location+GEM_WIDTH - 1," ");
            attroff(COLOR_PAIR(COLOR_BLACK));
            break;

        case 2:
            attron(COLOR_PAIR(COLOR_BLACK));
            mvwprintw(Window_1,y_location,x_location + 1," ");                  //..0..
            mvwprintw(Window_1,y_location,x_location+GEM_WIDTH - 2," ");        //.000.
            mvwprintw(Window_1,y_location + 1,x_location," ");                  //..0..
            mvwprintw(Window_1,y_location + 1,x_location+GEM_WIDTH - 1," ");
            mvwprintw(Window_1,y_location + 2,x_location + 1," ");
            mvwprintw(Window_1,y_location + 2,x_location+GEM_WIDTH - 2," ");
            attroff(COLOR_PAIR(COLOR_BLACK));
            break;

        case 3:
            attron(COLOR_PAIR(COLOR_BLACK));
            mvwprintw(Window_1,y_location,x_location + 2," ");                  //.....
            mvwprintw(Window_1,y_location + 2,x_location + 2," ");              //.000.
            attroff(COLOR_PAIR(COLOR_BLACK));                                   //.....
            break;

        case 4:
            attron(COLOR_PAIR(COLOR_BLACK));                                    //.....
            mvwprintw(Window_1,y_location + 1,x_location + 1," ");              //..0..
            mvwprintw(Window_1,y_location + 1,x_location+GEM_WIDTH - 2," ");    //.....
            attroff(COLOR_PAIR(COLOR_BLACK));
            break;

        default:
            break;
    }
}
