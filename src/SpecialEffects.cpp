#include "../include/SpecialEffects.h"

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
    mvwaddch(Window_1,y_location,x_location,'E');
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
    mvwaddch(Window_1,y_location,x_location,'L');
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
    mvwaddch(Window_1,y_location,x_location,'N');
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
    mvwaddch(Window_1,y_location,x_location,'S');
    attroff(COLOR_PAIR(COLOR_BLACK));
}
