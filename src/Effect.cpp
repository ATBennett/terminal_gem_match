#include "../include/Effect.h"

Effect::Effect(int x_loc, int y_loc, int n_length, WINDOW* window)
{
    x_location = x_loc;
    y_location = y_loc;
    cycle = 0;
    length = n_length;
    Window_1 = window;
}

Effect::~Effect()
{
    //dtor
}
