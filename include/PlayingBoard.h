//A masterclass to manage the gem grid and extra information.

#ifndef PLAYINGBOARD_H
#define PLAYINGBOARD_H

#include "GemGrid.h"
#include "definitions.h"

class PlayingBoard
{
    private:
        GemGrid Gem_Grid;

        WINDOW *Stats_Window;
        WINDOW *Grid_Window;
        WINDOW *Background_Window;

        int turns;
        float score;
        std::pair<int,int> cursor_pos; //cursor x,y
        bool highlight;

    public:
        PlayingBoard();
        virtual ~PlayingBoard();

        void printExtras();
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
