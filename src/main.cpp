#include <ncurses.h>
#include <string>
#include "../include/Board.h"

using namespace std;

int main()
{
    //ncurses initilisation
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

    Board MainBoard(8,8);   //Creates an 8x8 board
    MainBoard.setTurns(30);
    MainBoard.printBoard();
    vector<pair<int,int> > MatchedGems = MainBoard.matched(); //checks for any already matched gems
    while(!MatchedGems.empty()) //Keeps going until there are no more matches
    {
        MainBoard.quickRemoveMatched(MatchedGems);
        MatchedGems = MainBoard.matched();
    }

    //Main Gameplay loop
    while(MainBoard.getTurns()>0){
        clear();
        MainBoard.printBoard();
        refresh();
        int temp = toupper(getch());
        if(temp == KEY_UP) MainBoard.mvCursorV(-1);
        else if(temp == KEY_DOWN) MainBoard.mvCursorV(1);
        else if(temp == KEY_LEFT) MainBoard.mvCursorH(-1);
        else if(temp == KEY_RIGHT) MainBoard.mvCursorH(1);
        else if(temp == ' '){ //If space is pressed enters gem swapping mode
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
                default : dir = 'X'; break; //if an invalid key is pressed set dir to 'X' to avoid breaking the swapGems function
            }
            MainBoard.setHighlight(false);
            if(MainBoard.swapGems(MainBoard.getCursor(),dir)){
                clear();
                MainBoard.printBoard();
                refresh();
                if(!MainBoard.matched().empty()){
                    MainBoard.setTurns(MainBoard.getTurns() - 1);
                    while(!MainBoard.matched().empty()){ //Loops until there are no more matches
                        MainBoard.fancyRemoveMatched(MainBoard.matched());
                    }
                }
                else MainBoard.swapGems(MainBoard.getCursor(),dir); //If there are no matches, swap the gems back
            }
        }
    }
    MainBoard.printEnd();
    endwin();
}
