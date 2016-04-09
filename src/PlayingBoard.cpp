#include "../include/PlayingBoard.h"
#include <ncurses.h>

PlayingBoard::PlayingBoard()
: GemGrid1(BoardWidth,BoardHeight,1,0)
{
    cx = 0;
    cy = 0;
    turns = GameTurns;
    score = 0;
    highlight = false;

    while(!GemGrid1.matched().empty()){
        GemGrid1.quickRemoveMatched(GemGrid1.matched());
    }
}

PlayingBoard::~PlayingBoard()
{
    //dtor
}

void PlayingBoard::printEnding(){
    GemGrid1.printEnd();
    mvprintw(1,1,"Your Score: %.0f",score);
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
    GemGrid1.printGrid();
    attron(COLOR_PAIR(COLOR_BLACK));
    if(highlight) mvprintw(cy*GemHeight+2,cx*GemWidth+1,"+++++"); //Highlight changes the cursor
    else mvprintw(cy*GemHeight+2,cx*GemWidth+1,"=====");
    attroff(COLOR_PAIR(COLOR_BLACK));
    mvprintw(10,BoardWidth*GemWidth + 4,"Score: %.0f",score);
    mvprintw(11,BoardWidth*GemWidth + 4,"Turns Remaining: %d",turns);
    mvprintw(1,BoardWidth*GemWidth + 4,"Controls: ");
    mvprintw(3,BoardWidth*GemWidth + 4,"Arrow keys: move cursor");
    mvprintw(5,BoardWidth*GemWidth + 4,"Space bar: select Gem");
    mvprintw(7,BoardWidth*GemWidth + 4,"You must make a match");
    mvprintw(8,BoardWidth*GemWidth + 4,"for a move to be valid");
    return;
}
