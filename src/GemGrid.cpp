#include <iostream>
#include <ncurses.h>
#include <unistd.h>
//Implementation of the GemGrid class.

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
    while(!matched().empty())
    {
        quickRemoveGems(matched());
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
std::vector<std::pair<int,int> > GemGrid::matched()
{
    std::vector<std::pair<int,int> > gem_locs;
    //Loops through the entire matrix top down.
    for(int i = 0; i<grid_height; i++)
    {
        for(int j = 0; j<grid_width; j++)
        {
            //Horizontal matches.
            //Makes sure to ignore gems too close to the right edge to match.
            if(j < grid_width - 2 && Gem_Matrix[j][i] != NULL)
            {
                bool match = true;
                int match_length = 1;
                //Makes sure not to go out of bounds.
                while(match && j+match_length < grid_width)
                {
                    //Avoids null pointers.
                    if(Gem_Matrix[j+match_length][i] != NULL)
                    {
                        if(Gem_Matrix[j][i]->getColor() == Gem_Matrix[j+match_length][i]->getColor()) match_length++;
                        else match = false;
                    }
                    else match = false;
                }

                if(match_length >= 3)
                {
                    //From leftmost gem in a horizontal match, loops through.
                    for(int k = 0; k<match_length; k++)
                    {
                            gem_locs.push_back(std::make_pair(j+k,i));
                    }
                }
            }

            //Verticle matches
            //Makes sure to ignore gems too close to the bottom edge to match.
            if(i < grid_height - 2 && Gem_Matrix[j][i] != NULL)
            {
                int match_length = 1;
                bool match = true;
                while(match && i+match_length < grid_height)
                {
                    //Makes sure not to go out of bounds.
                    //Avoids null pointers.
                    if(Gem_Matrix[j][i+match_length] != NULL)
                    {
                        if(Gem_Matrix[j][i]->getColor() == Gem_Matrix[j][i+match_length]->getColor()) match_length++;
                        else match = false;
                    }
                    else match = false;
                }

                if(match_length >= 3)
                {
                    //From topmost gem in a verticle match, loops through
                    for(int k = 0; k<match_length; k++)
                    {
                        gem_locs.push_back(std::make_pair(j,i+k));
                    }
                }
            }

        }
    }

    //Removes duplicates.
    std::sort(gem_locs.begin(),gem_locs.end());
    gem_locs.erase(std::unique (gem_locs.begin(), gem_locs.end()), gem_locs.end());

    return gem_locs;
}

//Quickly swaps all matched gems for randomly generated ones.
void GemGrid::quickRemoveGems(std::vector<std::pair<int,int> > gem_locs)
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        delete Gem_Matrix[x][y];
        Gem_Matrix[x][y] = randGem();
    }
}

//Swaps the position of 2 Gem pointers.
//Returns false if this was not possible.
bool GemGrid::swapGems(std::pair<int,int> location, char direction)
{
    std::pair<int,int> dir_vector;
    Gem* Gem_Buffer;
    int first_x = location.first;
    int first_y = location.second;
    if(direction == 'U')
    {
        if(location.second <= 0) return false;
        else
        {
            dir_vector.first=0;
            dir_vector.second=-1;
        }
    }
    else if(direction == 'D')
    {
        if(location.second >= grid_height-1) return false;
        else
        {
            dir_vector.first=0;
            dir_vector.second=1;
        }
    }
    else if(direction == 'L')
    {
        if(location.first <= 0) return false;
        else
        {
            dir_vector.first=-1;
            dir_vector.second=0;
        }
    }
    else if(direction == 'R')
    {
        if(location.first >= grid_width - 1) return false;
        else
        {
            dir_vector.first=1;
            dir_vector.second=0;
        }
    }
    else return false;

    int second_x = first_x + dir_vector.first;
    int second_y = first_y + dir_vector.second;
    if(Gem_Matrix[first_x][first_y] != NULL && Gem_Matrix[second_x][second_y]!= NULL)
    {
        int loop_time = (GEM_HEIGHT * std::abs(dir_vector.second)) + (GEM_WIDTH * std::abs(dir_vector.first));
        int sleep_time = (SPEED*75000)/loop_time;
        //Swap animation.
        for(int i = 1; i <= loop_time; i++)
        {
            int move_x = i*dir_vector.first;
            int move_y = i*dir_vector.second;
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
        return true;
    }
    else return false;
}

//Finds the matches larger than 3 and runs the corresponding function.
//WIP.
void GemGrid::createSpecial(std::vector<std::pair<int,int> > gem_locs)
{
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        bool do_nothing_h = false;
        bool do_nothing_v = false;
        int match_h = 0;
        int match_v = 0;
        int curr_x = gem_locs[i].first;
        int curr_y = gem_locs[i].second;
        for(unsigned int j = 0; j< gem_locs.size(); j++)
        {
            int newX = gem_locs[j].first;
            int newY = gem_locs[j].second;
            if(Gem_Matrix[curr_x][curr_y]->getColor()==Gem_Matrix[newX][newY]->getColor())
            {
                if(newY == curr_y && newX == curr_x - 1) do_nothing_h = true;
                if(newX == curr_x && newY == curr_y - 1) do_nothing_v = true;
                if(!do_nothing_h && newY == curr_y)
                {
                    if(newX - curr_x > match_h) match_h = newX - curr_x;
                }
                if(!do_nothing_v && newX == curr_x)
                {
                    if(newY - curr_y > match_v) match_v = newY - curr_y;
                }
            }
        }
        if(!do_nothing_h)
        {
            if(match_h == 4) match4H(curr_x,curr_y);
            else if(match_h == 5) match5H(curr_x,curr_y);
            else if(match_h == 6) match6H(curr_x,curr_y);
        }
        if(!do_nothing_v)
        {
            if(match_v == 4) match4V(curr_x, curr_y);
            else if(match_v == 5) match5V(curr_x, curr_y);
            else if(match_v == 6) match6V(curr_x, curr_y);
        }
    }
    return;
}

//Takes a vector of pairs that contain the location of all the gems to be removed.
//Removes them with flair.
std::vector<std::pair<int,int> > GemGrid::getKilledGems(std::vector<std::pair<int,int> > gem_locs)
{
    //Getting all the gems to be removed via the kill coords function of a gem.
    std::vector<std::pair<int,int> > gem_kill_locs;
    std::vector<std::pair<int,int> > temp;
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        temp = Gem_Matrix[x][y]->getKillCoords(x,y);
        gem_kill_locs.insert(gem_kill_locs.end(), temp.begin(), temp.end()); //Inserts temp onto the end of the kill locations.
        temp.clear();
    }
    //Removes duplicates.
    std::sort(gem_kill_locs.begin(),gem_kill_locs.end());
    gem_kill_locs.erase(std::unique (gem_kill_locs.begin(), gem_kill_locs.end()), gem_kill_locs.end());

    if(gem_kill_locs.size()!=gem_locs.size()) //If there are new gems to be killed, runs again recursively
    {
        gem_kill_locs = getKilledGems(gem_kill_locs);
    }

    return gem_kill_locs;
}


//Takes a vector of pairs that contain the location of all the gems to be removed.
//Removes them with flair.
float GemGrid::fancyRemoveGems(std::vector<std::pair<int,int> > gem_locs)
{
    //Prints first shrink.
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        Gem_Matrix[x][y]->printVoid( x*GEM_WIDTH, y*GEM_HEIGHT, Window_1);
        Gem_Matrix[x][y]->printShrink1( x*GEM_WIDTH, y*GEM_HEIGHT, Window_1);
    }
    wrefresh(Window_1);
    usleep(SPEED*30000);
    //Prints second shrink.
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        Gem_Matrix[x][y]->printVoid(x*GEM_WIDTH, y*GEM_HEIGHT, Window_1);
        Gem_Matrix[x][y]->printShrink2(x*GEM_WIDTH, y*GEM_HEIGHT, Window_1);
    }
    wrefresh(Window_1);
    usleep(SPEED*30000);
    //Prints a void where a gem used to be.
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        Gem_Matrix[x][y]->printVoid(x*GEM_WIDTH, y*GEM_HEIGHT, Window_1);
    }
    wrefresh(Window_1);
    usleep(SPEED*30000);
    float rawScore = 0;
    float multiplier = 0;
    //Removes matched gems and adds onto the score.
    for(unsigned int i = 0; i < gem_locs.size(); i++)
    {
        int x = gem_locs[i].first;
        int y = gem_locs[i].second;
        rawScore += Gem_Matrix[x][y]->getScore();
        multiplier += Gem_Matrix[x][y]->getMultiplier();
        delete Gem_Matrix[x][y];  //Makes sure the object is deleted.
        Gem_Matrix[x][y] = NULL;  //Sets the pointer to null.
    }

    //Falls gems down and adds new random ones at the top.
    bool falling = true;
    while(falling)
    {
        falling = false;
        fallGems();
        for(int x = 0; x < grid_width; x++)
        {
            if( Gem_Matrix[x][0] == NULL )
            {
                falling = true;
                Gem_Matrix[x][0] = randGem();
            }
        }
        if(falling) fallGems();
    }
    return rawScore * multiplier;
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

// Not implemented yet
void GemGrid::match4H(int x, int y)
{
}
void GemGrid::match4V(int x, int y)
{
}
void GemGrid::match5H(int x, int y)
{
}
void GemGrid::match5V(int x, int y)
{
}
void GemGrid::match6H(int x, int y)
{
}
void GemGrid::match6V(int x, int y)
{
}
