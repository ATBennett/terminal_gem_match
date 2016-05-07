#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "../include/PlayingBoard.h"
#include "../include/definitions.h"

using namespace std;

//Makes sure the terminal window is larger than min_x and min_y, prints message and waits if not.
//Returns false if it needed to wait for a screen resize
bool checkWindowSize(int min_x, int min_y){
    int window_size_x;
    int window_size_y;
	getmaxyx( stdscr, window_size_y, window_size_x);
	bool output = true;
	WINDOW *errorWin = newwin(5,42, window_size_y/2 - 3, window_size_x/2 - 21);
    while(window_size_x < min_x || window_size_y < min_y)
    {
        wborder(errorWin,0,0,0,0,0,0,0,0);
        mvwprintw(errorWin,1,1,"Please increase window size,");
        if( window_size_x < min_x ) mvwprintw(errorWin,2,1,"Current Width: %d, Minimum Width: %d", window_size_x, min_x);
        if( window_size_y < min_y ) mvwprintw(errorWin,3,1,"Current Height: %d, Minimum Height: %d", window_size_y, min_y);
        wrefresh(errorWin);
        usleep(100000);
        getmaxyx( stdscr, window_size_y, window_size_x);
        wclear(errorWin);
        output = false;
    }
    delwin(errorWin);
    return output;
}

int main()
{
    //Calculating required terminal size.
    int min_x = GEM_WIDTH*BOARD_WIDTH + 27;
    int min_y = GEM_HEIGHT*BOARD_HEIGHT + 2;
    int last_x, last_y, curr_x, curr_y;
    getmaxyx( stdscr, curr_y, curr_x);

    //Ncurses initilisation.
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,TRUE);

    if(has_colors() == FALSE)
	{
        endwin();
		printf("Your terminal does not support color\n");
		return(1);
	}
	start_color();
	curs_set(0);
    refresh();

    //Makes sure the window is the right size before initialization.
    if(!checkWindowSize(min_x, min_y))
    {
        clear();
        refresh();
    }
    getmaxyx(stdscr, last_x,last_y);

    //Initialises the board.
    PlayingBoard Main_Board;
    Main_Board.initialise();
    Main_Board.printEverything();

    //Main Gameplay loop.
    while(Main_Board.getTurns()>0)
    {

        //Detects changes in window size.
        getmaxyx(stdscr, curr_x,curr_y);
        if(curr_x != last_x || curr_y != last_y)
        {
            checkWindowSize(min_x,min_y);
            Main_Board.resizeW();
            Main_Board.printEverything();
            getmaxyx(stdscr, last_x,last_y);
        }

        //Input detection.
        int temp = toupper(getch());
        switch(temp)
        {
            case KEY_UP :
                Main_Board.mvCursorV(-1);
                break;

            case KEY_DOWN :
                Main_Board.mvCursorV(1);
                break;

            case KEY_LEFT :
                Main_Board.mvCursorH(-1);
                break;

            case KEY_RIGHT :
                Main_Board.mvCursorH(1);
                break;

            case 'X' :
                Main_Board.resetGems();
                break;

            case ' ' :
            {
                //If space is pressed enters gem swapping mode.
                Main_Board.setHighlight(true);
                Main_Board.updateExtras();
                int temp2 = toupper(getch());
                char dir;
                switch(temp2)
                {
                    case KEY_UP : dir = 'U'; break;
                    case KEY_DOWN : dir = 'D'; break;
                    case KEY_LEFT : dir = 'L'; break;
                    case KEY_RIGHT : dir = 'R'; break;
                    //If an invalid key is pressed set dir to 'X' to avoid breaking the swapGems function.
                    default : dir = 'X'; break;
                }
                Main_Board.setHighlight(false);
                Main_Board.swapGem(dir);
                Main_Board.updateExtras();
                break;
            }

            default :
                break;
        }
    }
    //After turns has reached 0, it exits the while loop and prints the ending then closes the game
    Main_Board.printEnding();
    endwin();
}
