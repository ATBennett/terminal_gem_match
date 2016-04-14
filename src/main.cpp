#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "../include/PlayingBoard.h"
#include "../include/definitions.h"

using namespace std;

//Makes sure the terminal window is larger than minX and minY, prints message and waits if not.
//Returns false if it needed to wait for a screen resize
bool checkWindowSize(int minX, int minY){
    int WindowSizeX;
    int WindowSizeY;
	getmaxyx( stdscr, WindowSizeY, WindowSizeX);
	bool output = true;
	WINDOW *error_win = newwin(5,42, WindowSizeY/2 - 3, WindowSizeX/2 - 21);
    while(WindowSizeX < minX || WindowSizeY < minY){
        wclear(error_win);
        wborder(error_win,0,0,0,0,0,0,0,0);
        mvwprintw(error_win,1,1,"Please increase window size,");
        if( WindowSizeX < minX ) mvwprintw(error_win,2,1,"Current Width: %d, Minimum Width: %d", WindowSizeX, minX);
        if( WindowSizeY < minY ) mvwprintw(error_win,3,1,"Current Height: %d, Minimum Height: %d", WindowSizeY, minY);
        wrefresh(error_win);
        usleep(100000);
        getmaxyx( stdscr, WindowSizeY, WindowSizeX);
        wclear(error_win);
        output = false;
    }
    delwin(error_win);
    return output;
}

int main()
{
    //Calculating required terminal size.
    int minX = GemWidth*BoardWidth + 27;
    int minY = GemHeight*BoardHeight + 2;
    int lastX, lastY, curX, curY;
    getmaxyx( stdscr, curY, curX);

    //Ncurses initilisation.
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

    //Makes sure the window is the right size before initialization.
    if(!checkWindowSize(minX, minY)){
        clear();
        refresh();
    }
    getmaxyx(stdscr, lastX,lastY);

    //Initialises the board.
    PlayingBoard MainBoard;
    MainBoard.initialise();

    //Main Gameplay loop.
    while(MainBoard.getTurns()>0){

        //Detects changes in window size.
        getmaxyx(stdscr, curX,curY);
        if(curX != lastX || curY != lastY){
            checkWindowSize(minX,minY);
            MainBoard.resizeW();
            getmaxyx(stdscr, lastX,lastY);
        }

        MainBoard.printExtras();

        //Input detection.
        int temp = toupper(getch());
        if(temp == KEY_UP) MainBoard.mvCursorV(-1);
        else if(temp == KEY_DOWN) MainBoard.mvCursorV(1);
        else if(temp == KEY_LEFT) MainBoard.mvCursorH(-1);
        else if(temp == KEY_RIGHT) MainBoard.mvCursorH(1);
        else if(temp == 'X') MainBoard.resetGems();
        else if(temp == ' '){
            //If space is pressed enters gem swapping mode.
            MainBoard.setHighlight(true);
            MainBoard.printExtras();
            int temp2 = ERR;
            temp2 = toupper(getch());
            char dir;
            switch(temp2){
                case KEY_UP : dir = 'U'; break;
                case KEY_DOWN : dir = 'D'; break;
                case KEY_LEFT : dir = 'L'; break;
                case KEY_RIGHT : dir = 'R'; break;
                //If an invalid key is pressed set dir to 'X' to avoid breaking the swapGems function.
                default : dir = 'X'; break;
            }
            MainBoard.setHighlight(false);
            MainBoard.swapGem(dir);
        }
    }
    MainBoard.printEnding();
    endwin();
}
