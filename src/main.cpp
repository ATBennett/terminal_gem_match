#include <ncurses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <utility>
#include <ncurses.h>
#include "Board.h"

using namespace std;

int main()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,TRUE);

    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		return(1);
	}

	start_color();
	curs_set(0);
    Board MainBoard(8,8);
    MainBoard.setTurns(30);
    MainBoard.printBoard();
    vector<pair<int,int> > MatchedGems = MainBoard.matched();
    while(!MatchedGems.empty())
    {
        MainBoard.quickRemoveMatched(MatchedGems);
        MatchedGems = MainBoard.matched();
    }
    while(MainBoard.getTurns()>0){
        clear();
        MainBoard.printBoard();
        refresh();
        int temp = toupper(getch());
        if(temp == KEY_UP) MainBoard.mvCursorV(-1);
        else if(temp == KEY_DOWN) MainBoard.mvCursorV(1);
        else if(temp == KEY_LEFT) MainBoard.mvCursorH(-1);
        else if(temp == KEY_RIGHT) MainBoard.mvCursorH(1);
        else if(temp == ' '){
            clear();
            MainBoard.setHighlight(true);
            MainBoard.printBoard();
            refresh();
            int temp2 = '0';
            temp2 = toupper(getch());
            char dir;
            switch(temp2){
                case KEY_UP : dir = 'U'; break;
                case KEY_DOWN : dir = 'D'; break;
                case KEY_LEFT : dir = 'L'; break;
                case KEY_RIGHT : dir = 'R'; break;
                default : dir = 'X'; break;
            }
            MainBoard.setHighlight(false);
            if(MainBoard.swapGems(MainBoard.getCursor(),dir)){
                clear();
                MainBoard.printBoard();
                refresh();
                if(!MainBoard.matched().empty()){
                    MainBoard.setTurns(MainBoard.getTurns() - 1);
                    while(!MainBoard.matched().empty()){
                        MainBoard.fancyRemoveMatched(MainBoard.matched());
                    }
                }
                else MainBoard.swapGems(MainBoard.getCursor(),dir);
            }
        }
    }
    MainBoard.printEnd();
    endwin();
}
