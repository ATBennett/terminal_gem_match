//Implementation of the GemGrid class.

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <algorithm>
#include "../include/GemGrid.h"


GemGrid::GemGrid(unsigned int width, unsigned int height, WINDOW *Screen_1)
{
    srand(time(NULL));
    grid_height = height;
    grid_width = width;
    Window_1 = Screen_1;

    //Initialises the colors for ncurses (may move this).
    init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
    init_pair(COLOR_BLUE,COLOR_WHITE,COLOR_BLUE);
    init_pair(COLOR_CYAN,COLOR_BLACK,COLOR_CYAN);
    init_pair(COLOR_GREEN,COLOR_BLACK,COLOR_GREEN);
    init_pair(COLOR_MAGENTA,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(COLOR_RED,COLOR_BLACK,COLOR_RED);
    init_pair(COLOR_WHITE,COLOR_BLACK,COLOR_WHITE);
    init_pair(COLOR_YELLOW,COLOR_BLACK,COLOR_YELLOW);
}

GemGrid::~GemGrid()
{
    //dtor
}

void GemGrid::createRandomGrid()
{
    for(int i = 0; i < grid_height; i++)
    {
        for(int j = 0; j < grid_width; j++)
        {
            Gem_Matrix[j][i]=randGem();
        }
    }
    while(!getMatched().empty())
    {
        quickRemoveMatches(getMatched());
    }
}

//Animation to make gems appear as if they are falling onto the board.
void GemGrid::fallOntoBoard()
{
    Gem *Gem_Buffer[100][100];
    for(int y = 0; y < grid_height; y++)
    {
        for(int x = 0; x < grid_width; x++)
        {
            Gem_Buffer[x][y]=Gem_Matrix[x][y];
            Gem_Buffer[x][y]->setNew(true);
            Gem_Matrix[x][y]=NULL;
        }
    }
    //Loops backwards through the buffer matrix.
    for(int b_y = grid_height - 1; b_y >= 0; b_y--)
    {
        for(int x = 0; x < grid_width; x++)
        {
            Gem_Matrix[x][0]=Gem_Buffer[x][b_y];
        }
        fallGems();
        if(b_y != 0) fallGems();
    }
}

//Creates a new random gem and returns a pointer to it (make sure to delete gems after removal).
Gem* GemGrid::randGem()
{
    int rand_num = rand() % 7;
    switch(rand_num)
    {
        case 0 : return new RedGem();
        case 1 : return new GreenGem();
        case 2 : return new YellowGem();
        case 3 : return new BlueGem();
        case 4 : return new MagentaGem();
        case 5 : return new CyanGem();
        case 6 : return new WhiteGem();
        default : return NULL;
    }
}

//Loops through and tells each gem to print itself onto the terminal.
void GemGrid::printGrid(){
    for(int i = 0;i < grid_height;i ++)
    {
        for(int j = 0; j < grid_width; j++)
        {
            if(Gem_Matrix[j][i] == NULL)
            {
                //Creates a gem just to print a gem sized void.
                Gem* Temp_Gem = randGem();
                Temp_Gem->printVoid(j*GEM_WIDTH,i*GEM_HEIGHT,Window_1);
                delete Temp_Gem;
            }
            else if(!Gem_Matrix[j][i]->getNew())
            {
                Gem_Matrix[j][i]->printGem(j*GEM_WIDTH,i*GEM_HEIGHT,Window_1);
            }
            else if(Gem_Matrix[j][i]->getNew())
            {
               Gem_Matrix[j][i]->printVoid(j*GEM_WIDTH,i*GEM_HEIGHT,Window_1);
            }
        }
    }
}

//Returns a vector of pairs that give coordinates of gems that have been matched
std::vector<Match> GemGrid::getMatched()
{
    std::vector<Match> matches;
    //Loops through the entire matrix top down.
    for(int i = 0; i<grid_height; i++)
    {
        for(int j = 0; j<grid_width; j++)
        {

        }
    }
    return matches;
}

//Quickly swaps all matched gems for randomly generated ones.
void GemGrid::quickRemoveMatches(std::vector<Match> matches)
{
}

float GemGrid::swapGems(int first_x, int first_y, char dir)
{
    //Input checking
    if(first_x >= grid_width || first_y >= grid_height)
        return 0;

    else if(first_x < 0 || first_y < 0)
        return 0;

    int second_x;
    int second_y;
    switch(dir)
    {
        case 'U' :
            if(first_y > 0)
            {
                second_x = first_x;
                second_y = first_y - 1;
            }
            else
                return 0;
            break;

        case 'D' :
            if(first_y < grid_height-1)
            {
                second_x = first_x;
                second_y = first_y + 1;
            }
            else
                return 0;
            break;

        case 'L' :
            if(first_x > 0)
            {
                second_x = first_x - 1;
                second_y = first_y;
            }
            else
                return 0;
            break;

        case 'R' :
            if(first_x < grid_width - 1)
            {
                second_x = first_x + 1;
                second_y = first_y;
            }
            else
                return 0;
            break;

        default:
            return 0;
    }
    std::vector<Match> matches;
    if(Gem_Matrix[first_x][first_y]->getType() == 'N')
    {
        matches = color_nuke(first_x, first_y, second_x, second_y);
    }
    else
    {
        if(swapGemPosition(first_x, first_y, second_x, second_y) == ERR)
            return 0;

        matches = getMatched();
        if(matches.empty())
        {
            swapGemPosition(first_x, first_y, second_x, second_y);
            return 0;
        }
    }
    //Loop repeates until there are no more matches
    float score = 0;
    while(true)
    {
        bool special_activated = false;
        for(unsigned int i = 0; i < matches.size(); i++)
        {
            if(matches[i].getType() == 'S')
                special_activated = true;
        }
        if(special_activated)
        {
            score += fireSpecials(matches);
            fallGems();
            matches = getMatched();
        }
        else
        {
            score += removeMatches(matches);
            fallGems();
            matches = getMatched();
        }
        if(matches.empty())
            return score;
    }
}
//Swaps the position of 2 Gem pointers.
//Returns false if this was not possible.
int GemGrid::swapGemPosition(int first_x, int first_y, int second_x, int second_y)
{
    // Input checking
    if(first_x >= grid_width || first_y >= grid_height || second_x >= grid_width || second_y >= grid_height)
        return ERR;

    else if(first_x < 0 || first_y < 0 || second_x < 0 || second_y < 0)
        return ERR;

    if(Gem_Matrix[first_x][first_y] != NULL && Gem_Matrix[second_x][second_y]!= NULL)
    {
        Gem* Gem_Buffer;
        int vec_y = second_y - first_y;
        int vec_x = second_x - first_x;
        int loop_time = (GEM_HEIGHT * std::abs(vec_y)) + (GEM_WIDTH * std::abs(vec_x));   //
        int sleep_time = (SPEED*75000)/loop_time;
        //Swap animation.
        for(int i = 1; i <= loop_time; i++)
        {
            int move_x = i*vec_x;
            int move_y = i*vec_y;
            Gem_Matrix[first_x][first_y]->printVoid(first_x*GEM_WIDTH,first_y*GEM_HEIGHT, Window_1);
            Gem_Matrix[second_x][second_y]->printVoid(second_x*GEM_WIDTH,second_y*GEM_HEIGHT, Window_1);
            Gem_Matrix[second_x][second_y]->printGem(second_x*GEM_WIDTH-move_x,second_y*GEM_HEIGHT-move_y, Window_1);
            Gem_Matrix[first_x][first_y]->printGem(first_x*GEM_WIDTH+move_x,first_y*GEM_HEIGHT+move_y, Window_1);
            wrefresh(Window_1);
            usleep(sleep_time);
        }

        Gem_Buffer = Gem_Matrix[second_x][second_y];
        Gem_Matrix[second_x][second_y] = Gem_Matrix[first_x][first_y];
        Gem_Matrix[first_x][first_y] = Gem_Buffer;
        return 1;
    }
    else
        return ERR;
}

std::vector<Match> GemGrid::color_nuke(int first_x,int first_y,int second_x,int second_y)
{
    std::vector<Match> matches;
    return matches;
}

//Takes a vector of pairs that contain the location of all the gems to be removed.
//Removes them with flair.
float GemGrid::fireSpecials(std::vector<Match> matches)
{
    return 0;
}


//Takes a vector of pairs that contain the location of all the gems to be removed.
//Removes them with flair.
float GemGrid::removeMatches(std::vector<Match> matches)
{
    return 0;
}

//Makes the gems fall into blank spaces below them.
void GemGrid::fallGems()
{
    //Loops through the matrix from bottom up, and sets any gems that need to fall, to falling.
    for(int i = grid_height - 1; i > 0; i--)
    {
        for(int j = 0; j < grid_width; j++)
        {
            if(Gem_Matrix[j][i]==NULL)
            {
                if(Gem_Matrix[j][i-1]!=NULL) Gem_Matrix[j][i-1]->setFalling(true);
            }
            else if(Gem_Matrix[j][i]->getFalling())
            {
                if(Gem_Matrix[j][i-1]!=NULL) Gem_Matrix[j][i-1]->setFalling(true);
            }
        }
    }
    //Plays the falling animation b_y lots of loops.
    bool falling = false;
    for(int k = 1; k <= GEM_HEIGHT; k++)
    {
        for(int i = grid_height - 1; i >= 0; i--)
        {
            for(int j = 0; j < grid_width; j++)
            {
                if(Gem_Matrix[j][i]!=NULL)
                {
                    if(Gem_Matrix[j][i]->getFalling() && !Gem_Matrix[j][i]->getNew())
                    {
                        Gem_Matrix[j][i]->printVoid( j*GEM_WIDTH, i*GEM_HEIGHT, Window_1);
                        Gem_Matrix[j][i]->printGem( j*GEM_WIDTH, i*GEM_HEIGHT+k, Window_1);
                        falling = true;
                    }
                    else if(Gem_Matrix[j][i]->getNew())
                    {
                        Gem_Matrix[j][i]->printVoid( j*GEM_WIDTH, i*GEM_HEIGHT, Window_1);
                        Gem_Matrix[j][i]->printGem( j*GEM_WIDTH, i*GEM_HEIGHT+k - 3, Window_1);
                        falling = true;
                    }
                    else Gem_Matrix[j][i]->printGem(j*GEM_WIDTH,i*GEM_HEIGHT, Window_1);
                }
            }
        }
        wrefresh(Window_1);
        if(falling) usleep(SPEED*20000);
    }
    //Loops through the matrix from the bottom and shifts gems around in the Gem matrix.
    for(int i = grid_height - 1; i > 0; i--) //Doesn't include top row of gems.
    {
        for(int j = 0; j < grid_width; j++)
        {
            if(Gem_Matrix[j][i] == NULL)
            {
                if(Gem_Matrix[j][i-1] != NULL && !Gem_Matrix[j][i-1]->getNew()) //Checks if gem above is present and not new.
                {
                    Gem_Matrix[j][i] = Gem_Matrix[j][i-1];
                    Gem_Matrix[j][i]->setFalling(false);
                    Gem_Matrix[j][i-1] = NULL;
                }
            }
            else
            {
                Gem_Matrix[j][i]->setFalling(false);
                Gem_Matrix[j][i]->setNew(false); //If a gem isn't on the top row, makes sure it is set to old.
            }
        }
    }
    //Loops through the top row.
    for(int j = 0; j < grid_width; j++)
    {
        if(Gem_Matrix[j][0] != NULL)
        {
            Gem_Matrix[j][0]->setFalling(false);
            Gem_Matrix[j][0]->setNew(false);
        }
    }
}

//Prints all the gems falling off the screen in a fancy animation.
void GemGrid::fallAll()
{
    for( int y = grid_height - 1; y >= 0; y-- ) //Falls the gems until there are spaces between them all.
    {
        //Plays the falling animation.
        for(int h = 0; h < GEM_HEIGHT; h++)
        {
            for(int b_y = grid_height - 1; b_y >= y; b_y-- ) //Counts up from bottom to Y.
            {
                for(int x = 0; x < grid_width; x++)
                {
                    if(Gem_Matrix[x][b_y]!=NULL)
                    {
                        Gem_Matrix[x][b_y]->printVoid(x*GEM_WIDTH,b_y*GEM_HEIGHT+h,Window_1);
                        Gem_Matrix[x][b_y]->printGem(x*GEM_WIDTH,b_y*GEM_HEIGHT+h + 1,Window_1);
                    }
                }
            }
            wrefresh(Window_1);
            usleep(SPEED*15000);
        }
        //Moves the gems below y down one.
        for(int b_y = grid_height - 1; b_y >= y; b_y-- ) //Counts up from bottom to Y.
        {
            for(int x = 0; x < grid_width; x++)
            {
                if(Gem_Matrix[x][b_y]!=NULL)
                {
                    if(b_y < grid_height)
                    {
                        Gem_Matrix[x][b_y+1] = Gem_Matrix[x][b_y];
                        Gem_Matrix[x][b_y] = NULL;
                    }
                    else
                    {
                        delete Gem_Matrix[x][b_y];
                        Gem_Matrix[x][b_y] = NULL;
                    }
                }
            }
        }
    }
    for(int i = 1; i < grid_height; i++) // Keep falling until all the gems are off the board.
    {
        //Plays the falling animation.
        for(int h = 0; h < GEM_HEIGHT; h++)
        {
            for(int y = grid_height - 1; y >= 0; y-- )
            {
                for(int x = 0; x < grid_width; x++)
                {
                    if(Gem_Matrix[x][y]!=NULL)
                    {
                        Gem_Matrix[x][y]->printVoid(x*GEM_WIDTH,y*GEM_HEIGHT+h,Window_1);
                        Gem_Matrix[x][y]->printGem(x*GEM_WIDTH,y*GEM_HEIGHT+h + 1,Window_1);
                    }
                }
            }
            wrefresh(Window_1);
            usleep(SPEED*15000);
        }
        //Moves all the gems down one.
        for(int y = grid_height - 1; y >= 0; y-- )
        {
            for(int x = 0; x < grid_width; x++)
            {
                if(Gem_Matrix[x][y]!=NULL)
                {
                    if(y < grid_height)
                    {
                        Gem_Matrix[x][y+1] = Gem_Matrix[x][y];
                        Gem_Matrix[x][y] = NULL;
                    }
                    else
                    {
                        delete Gem_Matrix[x][y];
                        Gem_Matrix[x][y] = NULL;
                    }
                }
            }
        }
    }
}
