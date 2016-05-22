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
    for(int y = y_location; y < y_location + GEM_HEIGHT; y++)
    {
        for(int x = x_location; x < x_location + GEM_WIDTH; x++)
        {
            mvwaddch(Window_1, y, x, 'L');
        }
    }
    attroff(COLOR_PAIR(COLOR_BLACK));
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
