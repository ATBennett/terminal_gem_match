#include <ncurses.h>
#include <string>
#include "../include/PlayingBoard.h"

#define GemHeight 3
#define GemWidth 5
#define speed 3

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

    PlayingBoard MainBoard;   //Creates the board

    //Main Gameplay loop
    while(MainBoard.getTurns()>0){
        clear();
        MainBoard.print();
        refresh();
        int temp = toupper(getch());
        if(temp == KEY_UP) MainBoard.mvCursorV(-1);
        else if(temp == KEY_DOWN) MainBoard.mvCursorV(1);
        else if(temp == KEY_LEFT) MainBoard.mvCursorH(-1);
        else if(temp == KEY_RIGHT) MainBoard.mvCursorH(1);
        else if(temp == ' '){ //If space is pressed enters gem swapping mode
            clear();
            MainBoard.setHighlight(true);
            MainBoard.print();
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
            MainBoard.swapGem(dir);
        }
    }
    MainBoard.printEnding();
    endwin();
}
