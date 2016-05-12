#ifndef EFFECT_H
#define EFFECT_H

#include <ncurses.h>

class Effect
{
    public:
        Effect(int,int,int,WINDOW*);
        virtual ~Effect();

        virtual void playEffect(){ cycle++; }

    protected:
        int cycle;
        int length;
        int x_location;
        int y_location;
        WINDOW* Window_1;
};

#endif // EFFECT_H
