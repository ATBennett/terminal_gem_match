#include "../include/PlayingBoard.h"
#include <unistd.h>
#include <ncurses.h>

PlayingBoard::PlayingBoard()
: Gem_Grid(BOARD_WIDTH,BOARD_HEIGHT, newwin(GEM_HEIGHT*BOARD_HEIGHT,GEM_WIDTH*BOARD_WIDTH,1,1))
{
    cursor_x = 0;
    cursor_y = 0;
    turns = GAME_TURNS;
    score = 0;
    highlight = false;

    Grid_Window = Gem_Grid.getWindow();
    Stats_Window = newwin(GEM_HEIGHT*BOARD_HEIGHT, 24, 0, GEM_WIDTH*BOARD_WIDTH + 3);
    Background_Window = newwin(GEM_HEIGHT*BOARD_HEIGHT + 2,GEM_WIDTH*BOARD_WIDTH + 2,0,0);
    wrefresh(Grid_Window);
    wrefresh(Stats_Window);

}

PlayingBoard::~PlayingBoard()
{
    //dtor
}

void PlayingBoard::printEnding()
{
    Gem_Grid.fallAll();
    clear();
    mvprintw(1,1,"Your Score: %.0f",score);
    refresh();
    usleep(5000000);
}

void PlayingBoard::mvCursorH(int val)
{
    if(cursor_x + val < BOARD_WIDTH && cursor_x + val >= 0)
    {
        Gem_Grid.removeCursor(cursor_x,cursor_y);
        cursor_x = cursor_x+val;
        Gem_Grid.printCursor(cursor_x,cursor_y,"=====");
        wrefresh(Grid_Window);
    }
}

void PlayingBoard::mvCursorV(int val)
{
    if(cursor_y + val < BOARD_HEIGHT && cursor_y + val >= 0)
    {
        Gem_Grid.removeCursor(cursor_x,cursor_y);
        cursor_y = cursor_y+val;
        Gem_Grid.printCursor(cursor_x,cursor_y,"=====");
        wrefresh(Grid_Window);
    }
}

void PlayingBoard::swapGem(char dir)
{
    float tmp = Gem_Grid.swapGems(cursor_x,cursor_y,dir);
    if( tmp != 0)
    {
        score += tmp;
        turns--;
    }
}

void PlayingBoard::initialise()
{
    wborder(Background_Window,0,0,0,0,0,0,0,0);
    wrefresh(Background_Window);
    printEverything();
    Gem_Grid.createRandomGrid();
    Gem_Grid.fallOntoBoard();
}

void PlayingBoard::updateExtras()
{
    //Printing the cursor into the Grid_Window.
    if(highlight) Gem_Grid.printCursor(cursor_x,cursor_y,"+++++"); //Highlight changes the cursor
    else Gem_Grid.printCursor(cursor_x,cursor_y,"=====");

    //Printing extra info.
    mvwprintw( Stats_Window, 13, 1,"Score:             ");
    mvwprintw( Stats_Window, 14, 1,"Turns Remaining:             ");
    mvwprintw( Stats_Window, 13, 1,"Score: %.0f",score);
    mvwprintw( Stats_Window, 14, 1,"Turns Remaining: %d",turns);

    wrefresh(Grid_Window);
    wrefresh(Stats_Window);
}

void PlayingBoard::printEverything()
{

    wclear(Stats_Window);
    Gem_Grid.printGrid();
    //Printing the cursor into the Grid_Window.
    if(highlight) Gem_Grid.printCursor(cursor_x,cursor_y,"+++++"); //Highlight changes the cursor
    else Gem_Grid.printCursor(cursor_x,cursor_y,"=====");

    //Printing extra info.
    mvwprintw( Stats_Window, 1, 1,"Controls: ");
    mvwprintw( Stats_Window, 3, 1,"Arrow keys: move cursor");
    mvwprintw( Stats_Window, 5, 1,"Space bar: select Gem");
    mvwprintw( Stats_Window, 7, 1,"X: Reset board");
    mvwprintw( Stats_Window, 8, 1,"(Costs 1 turn)");
    mvwprintw( Stats_Window, 10, 1,"You must make a match");
    mvwprintw( Stats_Window, 11, 1,"for a move to be valid");
    mvwprintw( Stats_Window, 13, 1,"Score: %.0f",score);
    mvwprintw( Stats_Window, 14, 1,"Turns Remaining: %d",turns);

    wrefresh(Grid_Window);
    wrefresh(Stats_Window);
}

void PlayingBoard::resetGems()
{
    if(turns > 1)
    {
        Gem_Grid.fallAll();
        Gem_Grid.createRandomGrid();
        Gem_Grid.fallOntoBoard();
        turns = turns - 1;
    }
    else
    {
        printEnding();
    }
}

void PlayingBoard::resizeW()
{
    clear();
    refresh();
    wresize(Grid_Window,GEM_HEIGHT*BOARD_HEIGHT, GEM_WIDTH*BOARD_WIDTH);
    wresize(Background_Window,GEM_HEIGHT*BOARD_HEIGHT+2, GEM_WIDTH*BOARD_WIDTH+2);
    wresize(Stats_Window, GEM_HEIGHT*BOARD_HEIGHT, 24);
    wborder(Background_Window,0,0,0,0,0,0,0,0);
    wrefresh(Background_Window);
    printEverything();
}
