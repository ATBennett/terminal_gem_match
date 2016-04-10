#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "../include/PlayingBoard.h"

#define GemHeight 3
#define GemWidth 5
#define speed 3

using namespace std;

//makes sure the terminal window is larger than minX and minY, prints message and waits if not
bool checkWindowSize(int minX, int minY){
    int WindowSizeX;
    int WindowSizeY;
	getmaxyx( stdscr, WindowSizeY, WindowSizeX);
	bool output = true;
    while(WindowSizeX < minX || WindowSizeY < minY){
        output = false;
        clear();
        mvprintw(0,0,"Please increase window size,");
        if( WindowSizeX < minX ) mvprintw(1,0,"Current Width: %d, Minimum Width: %d", WindowSizeX, minX);
        if( WindowSizeY < minY ) mvprintw(2,0,"Current Height: %d, Minimum Height: %d", WindowSizeY, minY);
        refresh();
        usleep(100000);
        getmaxyx( stdscr, WindowSizeY, WindowSizeX);
    }
    return output;
}

int main()
{
    //Calculating required terminal size
    int minX = GemWidth*BoardWidth + 27;
    int minY = GemHeight*BoardHeight + 2;

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
    refresh();

    PlayingBoard MainBoard;   //Creates the board

    //Main Gameplay loop
    while(MainBoard.getTurns()>0){
        if(!checkWindowSize(minX, minY)) MainBoard.resizeW();
        MainBoard.print();
        refresh();
        int temp = toupper(getch());
        if(temp == KEY_UP) MainBoard.mvCursorV(-1);
        else if(temp == KEY_DOWN) MainBoard.mvCursorV(1);
        else if(temp == KEY_LEFT) MainBoard.mvCursorH(-1);
        else if(temp == KEY_RIGHT) MainBoard.mvCursorH(1);
        else if(temp == ' '){ //If space is pressed enters gem swapping mode
            MainBoard.setHighlight(true);
            MainBoard.print();
            int temp2 = ERR;
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
