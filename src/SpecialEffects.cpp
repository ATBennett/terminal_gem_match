#include "../include/SpecialEffects.h"
#include "../include/definitions.h"
#include <math.h>

ExplosionEffect::ExplosionEffect(int x_loc, int y_loc, int length, WINDOW* Window_1)
: Effect( x_loc, y_loc, length, Window_1 )
{
    //ctor
}

ExplosionEffect::~ExplosionEffect()
{
    //dtor
}

void ExplosionEffect::playEffect()
{
    attron(COLOR_PAIR(COLOR_BLACK));
    for(int y = y_location; y < y_location + GEM_HEIGHT; y++)
    {
        for(int x = x_location; x < x_location + GEM_WIDTH; x++)
        {
            mvwaddch(Window_1, y, x, 'E');
        }
    }
    attroff(COLOR_PAIR(COLOR_BLACK));
}

LightningEffect::LightningEffect(int x_loc, int y_loc, int length, WINDOW* Window_1)
: Effect( x_loc, y_loc, length, Window_1 )
{
    //ctor
}

LightningEffect::~LightningEffect()
{
    //dtor
}

void LightningEffect::playEffect()
{
    attron(COLOR_PAIR(COLOR_BLACK));
    if(cycle < length)
    {
        wattron(Window_1,COLOR_PAIR(COLOR_CYAN));
        cycle++;
        //Colors the soecial gem cyan
        for(int y = y_location; y < y_location + GEM_HEIGHT; y++)
            for(int x = 0; x < GEM_WIDTH*BOARD_WIDTH; x++)
                mvwaddch(Window_1,y,x,' ');

        for(int x = x_location; x < x_location + GEM_WIDTH; x++)
            for(int y = 0; y < GEM_HEIGHT*BOARD_HEIGHT; y++)
                mvwaddch(Window_1,y,x,' ');
        
        int down_lines = GEM_HEIGHT*BOARD_HEIGHT - (y_location + (GEM_HEIGHT - 1));
        int right_lines = GEM_WIDTH*BOARD_WIDTH - (x_location + (GEM_WIDTH - 1));
        wattroff(Window_1,COLOR_PAIR(COLOR_CYAN));
    }
}

ColorNukeEffect::ColorNukeEffect(int x_loc, int y_loc, int length, WINDOW* Window_1)
: Effect( x_loc, y_loc, length, Window_1 )
{
    //ctor
}

ColorNukeEffect::~ColorNukeEffect()
{
    //dtor
}

void ColorNukeEffect::playEffect()
{
    attron(COLOR_PAIR(COLOR_BLACK));
    for(int y = y_location; y < y_location + GEM_HEIGHT; y++)
    {
        for(int x = x_location; x < x_location + GEM_WIDTH; x++)
        {
            mvwaddch(Window_1, y, x, 'N');
        }
    }
    attroff(COLOR_PAIR(COLOR_BLACK));
}

StarNukeEffect::StarNukeEffect(int x_loc, int y_loc, int length, WINDOW* Window_1)
: Effect( x_loc, y_loc, length, Window_1 )
{
    //ctor
}

StarNukeEffect::~StarNukeEffect()
{
    //dtor
}

void StarNukeEffect::playEffect()
{
    attron(COLOR_PAIR(COLOR_BLACK));
    for(int y = y_location; y < y_location + GEM_HEIGHT; y++)
    {
        for(int x = x_location; x < x_location + GEM_WIDTH; x++)
        {
            mvwaddch(Window_1, y, x, 'S');
        }
    }
    attroff(COLOR_PAIR(COLOR_BLACK));
}
