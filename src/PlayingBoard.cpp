#include "../include/PlayingBoard.h"
#include <unistd.h>
#include <ncurses.h>

PlayingBoard::PlayingBoard()
: GemGrid1(BoardWidth,BoardHeight, newwin(GemHeight*BoardHeight,GemWidth*BoardWidth,1,1))
{
    cx = 0;
    cy = 0;
    turns = GameTurns;
    score = 0;
    highlight = false;

    while(!GemGrid1.matched().empty()){
        GemGrid1.quickRemoveMatched(GemGrid1.matched());
    }

    gridWindow = GemGrid1.getWindow();
    statsWindow = newwin(GemHeight*BoardHeight, 27, 0, GemWidth*BoardWidth + 3);
    wrefresh(gridWindow);
    wrefresh(statsWindow);

}

PlayingBoard::~PlayingBoard()
{
    //dtor
}

void PlayingBoard::printEnding(){
    GemGrid1.fallAll();
    clear();
    mvprintw(1,1,"Your Score: %.0f",score);
    refresh();
    usleep(5000000);
}

void PlayingBoard::mvCursorH(int val){
    if(cx + val < BoardWidth && cx + val >= 0){
        cx = cx+val;
    }
}

void PlayingBoard::mvCursorV(int val){
    if(cy + val < BoardHeight && cy + val >= 0){
        cy = cy+val;
    }
}

void PlayingBoard::swapGem(char dir){
    GemGrid1.swapGems(std::make_pair(cx,cy),dir);
    if(GemGrid1.matched().empty()) GemGrid1.swapGems(std::make_pair(cx,cy),dir);
    else{
        while(!GemGrid1.matched().empty()){
            score = score + GemGrid1.fancyRemoveMatched(GemGrid1.matched());
        }
        turns--;
    }
}

void PlayingBoard::print(){

    wclear(gridWindow);
    wclear(statsWindow);

    GemGrid1.printGrid();

    //Printing the cursor
    wattron( gridWindow, COLOR_PAIR(COLOR_BLACK));
    if(highlight) mvwprintw( gridWindow, cy*GemHeight+2,cx*GemWidth,"+++++"); //Highlight changes the cursor
    else mvwprintw( gridWindow, cy*GemHeight+2,cx*GemWidth,"=====");
    wattroff( gridWindow, COLOR_PAIR(COLOR_BLACK));

    //Printing extra info
    mvwprintw( statsWindow, 1, 1,"Controls: ");
    mvwprintw( statsWindow, 3, 1,"Arrow keys: move cursor");
    mvwprintw( statsWindow, 5, 1,"Space bar: select Gem");
    mvwprintw( statsWindow, 7, 1,"You must make a match");
    mvwprintw( statsWindow, 8, 1,"for a move to be valid");
    mvwprintw( statsWindow, 10, 1,"Score: %.0f",score);
    mvwprintw( statsWindow, 11, 1,"Turns Remaining: %d",turns);

    //Creates a window to draw around the Gem Grid for a border
    WINDOW *backgroundWindow = newwin(GemHeight*BoardHeight + 2,GemWidth*BoardWidth + 2,0,0);
    wborder(backgroundWindow,0,0,0,0,0,0,0,0);
    wrefresh(backgroundWindow);
    delwin(backgroundWindow);

    wrefresh(gridWindow);

    wrefresh(statsWindow);
}

void PlayingBoard::resizeW(){
    wresize(gridWindow,GemHeight*BoardHeight, GemWidth*BoardWidth);
}
