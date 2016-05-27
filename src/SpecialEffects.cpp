#include "../include/SpecialEffects.h"
#include "../include/cfg.h"
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
    for(int y = y_location; y < y_location + cfg::gem_height; y++)
    {
        for(int x = x_location; x < x_location + cfg::gem_width; x++)
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
        for(int y = y_location; y < y_location + cfg::gem_height; y++)
            for(int x = 0; x < cfg::gem_width*cfg::board_width; x++)
                mvwaddch(Window_1,y,x,' ');

        for(int x = x_location; x < x_location + cfg::gem_width; x++)
            for(int y = 0; y < cfg::gem_height*cfg::board_height; y++)
                mvwaddch(Window_1,y,x,' ');

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
    for(int y = y_location; y < y_location + cfg::gem_height; y++)
    {
        for(int x = x_location; x < x_location + cfg::gem_width; x++)
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
    for(int y = y_location; y < y_location + cfg::gem_height; y++)
    {
        for(int x = x_location; x < x_location + cfg::gem_width; x++)
        {
            mvwaddch(Window_1, y, x, 'S');
        }
    }
    attroff(COLOR_PAIR(COLOR_BLACK));
}
