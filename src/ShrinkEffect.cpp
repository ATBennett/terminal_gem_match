#include "../include/ShrinkEffect.h"
#include "../include/definitions.h"
#include <math.h>

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
    if(cycle < length)
    {
        cycle++;
        wattron(Window_1, COLOR_PAIR(COLOR_BLACK));
        int shrink_lines[GEM_HEIGHT];
        float line_weight = 200/GEM_HEIGHT;
        for(int i = 0; i < GEM_HEIGHT; i++)
        {
            //if i is in the second half of the gem, copies from first half
            //supposed to work with both even and odd gem heights
            if(i > (GEM_HEIGHT-1)/2)
            {
                shrink_lines[i]=shrink_lines[(GEM_HEIGHT-1)-i];
            }
            else
            {
                //Works out when a line should be blanked out by
                float line_lifespan = ((line_weight * length)/100) * (i + 1);
                //Cropping in instance of low line numbers + low animation length
                if(line_lifespan > length)
                    line_lifespan = length;

                //Calculates the number of blank chars to be deleted each cycle relative to when each line should be blanked out by
                float remove_num = ceil(((GEM_WIDTH / 2) / line_lifespan) * cycle);

                shrink_lines[i] = remove_num;
                //Makes sure the blanj char amount does not go ever the maximum
                if(shrink_lines[i] > (GEM_WIDTH/2) + 1)
                   shrink_lines[i] = (GEM_WIDTH/2) + 1;
            }
        }
        //Printing the blank spaces around the gem
        for(int i = 0; i < GEM_HEIGHT; i++)
        {
            int y = y_location + i;
            int x = x_location;
            for(int j = 0; j < shrink_lines[i]; j++)
            {
                mvwaddch(Window_1,y,x+j,' ');
                mvwaddch(Window_1,y,x+GEM_WIDTH - (j+1),' ');
            }
        }
        wattroff(Window_1, COLOR_PAIR(COLOR_BLACK));
    }
}
