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
    int x_step = 1+(cfg::gem_width*cfg::board_width)/(length-1);
    int y_step = 1+(cfg::gem_height*cfg::board_height)/(length-1);

    if(cycle < length)
    {
        int max_x = x_location + cfg::gem_width + (x_step*cycle);
        int min_x = x_location - (x_step*cycle);
        int max_y = y_location + cfg::gem_height + (y_step*cycle);
        int min_y = y_location - (y_step*cycle);
        
        if(min_x < 0)
            min_x = 0;
        
        if(min_y < 0)
            min_y = 0;
        
        if(max_x > cfg::gem_width*cfg::board_width)
            max_x = cfg::gem_width*cfg::board_width;
        
        if(max_y > cfg::gem_height*cfg::board_height)
            max_y = cfg::gem_height*cfg::board_height; 

        wattron(Window_1,COLOR_PAIR(COLOR_CYAN));
        for(int y = y_location; y < y_location + cfg::gem_height; y++)
            for(int x = min_x; x < max_x; x++)
                mvwaddch(Window_1,y,x,' ');

        for(int x = x_location; x < x_location + cfg::gem_width; x++)
            for(int y = min_y; y < max_y; y++)
                mvwaddch(Window_1,y,x,' ');

        wattroff(Window_1,COLOR_PAIR(COLOR_CYAN));
        cycle++;
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
