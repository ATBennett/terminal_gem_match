#ifndef PLAYINGBOARD_H
#define PLAYINGBOARD_H

#include "GemGrid.h"
#include "definitions.h"

class PlayingBoard
{
    private:
        GemGrid GemGrid1;
        int turns;
        float score;
        int cx;
        int cy;
        bool highlight;

    public:
        PlayingBoard();
        virtual ~PlayingBoard();

        void print();
        void mvCursorV(int);
        void mvCursorH(int);
        void swapGem(char);
        void printEnding();

        //setters and getters
        int getTurns() { return turns; }
        void setHighlight(bool val) { highlight = val; }
    protected:
};

#endif // PLAYINGBOARD_H
