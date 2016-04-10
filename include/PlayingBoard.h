//A masterclass to manage the gem grid and extra information

#ifndef PLAYINGBOARD_H
#define PLAYINGBOARD_H

#include "GemGrid.h"
#include "definitions.h"

class PlayingBoard
{
    private:
        GemGrid GemGrid1;

        WINDOW *statsWindow;
        WINDOW *gridWindow;

        int turns;
        float score;
        int cx;     //Cursor X coordinate
        int cy;     //Cursor Y coordinate
        bool highlight;

    public:
        PlayingBoard();
        virtual ~PlayingBoard();

        void print();
        void mvCursorV(int);
        void mvCursorH(int);
        void swapGem(char);
        void printEnding();
        void resizeW();

        //setters and getters
        int getTurns() { return turns; }
        void setHighlight(bool val) { highlight = val; }
    protected:
};

#endif // PLAYINGBOARD_H
