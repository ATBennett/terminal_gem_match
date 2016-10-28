//A masterclass to manage the gem grid and extra information.

#ifndef PLAYINGBOARD_H
#define PLAYINGBOARD_H

#include "GemGrid.h"

class PlayingBoard
{
    private:
        GemGrid Gem_Grid;

        WINDOW *Stats_Window;
        WINDOW *Grid_Window;
        WINDOW *Background_Window;

        bool _debug;
        int turns;
        float score;
        int cursor_x;
        int cursor_y;
        bool highlight;

    public:
        PlayingBoard(bool);
        virtual ~PlayingBoard();

        void updateExtras();
        void printEverything();
        void initialise();
        void resetGems();
        void mvCursorV(int);
        void mvCursorH(int);
        void swapGem(char);
        void printEnding();
        void resizeW();

        //Setters and getters.
        int getTurns() { return turns; }
        void setHighlight(bool val) { highlight = val; }
    protected:
};

#endif // PLAYINGBOARD_H
