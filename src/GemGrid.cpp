//Implementation of the GemGrid class.

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <algorithm>
#include "../include/GemGrid.h"


GemGrid::GemGrid(unsigned int width, unsigned int height, WINDOW* Screen_1)
{
    srand(time(nullptr));
    grid_height = height;
    grid_width = width;
    Window_1 = Screen_1;

    //Sets entire grid to nullptr
    for(int x = 0; x < MAX_BOARD_WIDTH; x++)
        for(int y = 0; y < MAX_BOARD_HEIGHT; y++)
            Gem_Matrix[x][y]=nullptr;

    //Initialises the colors for ncurses (may move this).
    init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
    init_pair(COLOR_NUKE,COLOR_BLACK,COLOR_BLACK);
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
    delwin(Window_1);
    for(int y = 0; y < MAX_BOARD_HEIGHT; y++)
    {
        for(int x = 0; x < MAX_BOARD_WIDTH; x++)
        {
            if(Gem_Matrix[x][y] != nullptr)
            {
                delete Gem_Matrix[x][y];
                Gem_Matrix[x][y] = nullptr;
            }
        }
    }
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
    Gem* Gem_Buffer[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT];
    for(int y = 0; y < grid_height; y++)
    {
        for(int x = 0; x < grid_width; x++)
        {
            Gem_Buffer[x][y]=Gem_Matrix[x][y];
            Gem_Buffer[x][y]->setNew(true);
            Gem_Matrix[x][y]=nullptr;
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
        default : return nullptr;
    }
}

//Loops through and tells each gem to print itself onto the terminal.
void GemGrid::printGrid(){
    for(int i = 0;i < grid_height;i ++)
    {
        for(int j = 0; j < grid_width; j++)
        {
            if(Gem_Matrix[j][i] == nullptr)
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
    std::vector<std::pair<int,int> > made_matches_h;
    std::vector<std::pair<int,int> > made_matches_v;
    //Loops through the entire matrix top down.
    for(int y = 0; y<grid_height; y++)
    {
        for(int x = 0; x<grid_width; x++)
        {
            bool skip_h = false;
            bool skip_v = false;
            //Checking if a horizontal match has already been made that includes this gem.
            for(unsigned int i = 0; i < made_matches_h.size(); i++)
            {
                if(made_matches_h[i].first == x && made_matches_h[i].second == y)
                    skip_h = true;
            }
            //Checking if a verticle match has already been made that includes this gem.
            for(unsigned int i = 0; i < made_matches_v.size(); i++)
            {
                if(made_matches_v[i].first == x && made_matches_v[i].second == y)
                    skip_v = true;
            }
            if(!skip_h)
            {
                std::vector<std::pair<int,int> > h_matches;
                h_matches = matchH(x,y);
                if(!h_matches.empty())
                {
                    matches.push_back(Match(h_matches));
                    made_matches_h.insert(made_matches_h.end(), h_matches.begin(), h_matches.end());
                }
            }
            if(!skip_v)
            {
                std::vector<std::pair<int,int> > v_matches;
                v_matches = matchV(x,y);
                if(!v_matches.empty())
                {
                    matches.push_back(Match(v_matches));
                    made_matches_v.insert(made_matches_v.end(), v_matches.begin(), v_matches.end());
                }
            }
        }
    }

    matches = intersectMatches(matches);
    return matches;
}

//From leftmost position, checks for a horizontal match, returns locations of all matched gems
std::vector<std::pair<int,int> > GemGrid::matchH(int x,int y)
{
    std::vector<std::pair<int,int> > matches_h;
    if(x < grid_width && Gem_Matrix[x][y]!=nullptr)
    {
        bool matching = true;
        for(int new_x = x; new_x < grid_width && matching; new_x++)
        {
            if(Gem_Matrix[new_x][y] != nullptr)
            {
                if(Gem_Matrix[x][y]->getColor() == Gem_Matrix[new_x][y]->getColor())
                    matches_h.push_back(std::make_pair(new_x,y));
                else
                    matching = false;
            }
            else
                matching = false;
        }
    }
    //Makes sure to only return matches 3 or larger
    if(matches_h.size() < 3)
        matches_h.clear();

    return matches_h;
}

//from topmost position, checks for a verticle match
std::vector<std::pair<int,int> > GemGrid::matchV(int x,int y)
{
    std::vector<std::pair<int,int> > matches_v;
    if(x < grid_height && Gem_Matrix[x][y]!=nullptr)
    {
        bool matching = true;
        for(int new_y = y; new_y < grid_width && matching; new_y++)
        {
            if(Gem_Matrix[x][new_y] != nullptr)
            {
                if(Gem_Matrix[x][y]->getColor() == Gem_Matrix[x][new_y]->getColor())
                    matches_v.push_back(std::make_pair(x,new_y));
                else
                    matching = false;
            }
            else
                matching = false;
        }
    }
    //Makes sure to only return matches 3 or larger
    if(matches_v.size() < 3)
        matches_v.clear();

    return matches_v;
}

//Checks if any matches are intersecting, then joins them.
//There is probably a much better way of doing this.
std::vector<Match> GemGrid::intersectMatches(std::vector<Match> matches)
{
    bool found_intersect = true;
    while(found_intersect)
    {
        found_intersect = false;
        int num_matches = matches.size();
        for(int i = 0; i < num_matches && !found_intersect; i++)
        {
            std::vector<std::pair<int,int> > first_match_locs = matches[i].getGemLocs();
            for(int j = i+1; j < num_matches && !found_intersect; j++)
            {
                std::vector<std::pair<int,int> > second_match_locs = matches[j].getGemLocs();
                for(unsigned int k = 0; k < first_match_locs.size() && !found_intersect; k++)
                {
                    std::pair<int,int> first_gem_loc = first_match_locs[k];
                    for(unsigned int l = 0; l < second_match_locs.size() && !found_intersect; l++)
                    {
                        std::pair<int,int> second_gem_loc = second_match_locs[l];
                        if(first_gem_loc == second_gem_loc)
                            found_intersect = true;
                    }
                }
                if(found_intersect)
                {
                    //Joins the intersecting match locations
                    first_match_locs.insert(first_match_locs.end(),second_match_locs.begin(),second_match_locs.end());
                    //Sorts and removes any repeated locations
                    std::sort(first_match_locs.begin(), first_match_locs.end());
                    //first_match_locs.erase(std::unique(first_match_locs.begin(), first_match_locs.end(), first_match_locs.end()));
                    //Erase old matches
                    matches.erase(matches.begin() + i);
                    matches.erase(matches.begin() + j);
                    //Add on new match
                    matches.push_back(Match(first_match_locs));
                }
            }
        }
    }
    return matches;
}

//Quickly swaps all matched gems for randomly generated ones.
void GemGrid::quickRemoveMatches(std::vector<Match> matches)
{
    for( unsigned int i = 0; i < matches.size(); i++)
    {
        matches[i].replaceWithRand(Gem_Matrix);
    }
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

    if(Gem_Matrix[first_x][first_y] == nullptr || Gem_Matrix[second_x][second_y] == nullptr)
        return 0;

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
            if(SWAP_BACK)
                swapGemPosition(first_x, first_y, second_x, second_y);
            return 0;
        }
    }
    //Loop repeates until there are no more matches
    float score = 0;
    while(true)
    {
        score += removeMatches(matches);

        bool falling = true;
        while(falling)
        {
            falling  = false;
            fallGems();
            for(int x = 0; x < grid_width; x++)
            {
                if(Gem_Matrix[x][0] == nullptr)
                {
                    falling = true;
                    Gem_Matrix[x][0] = randGem();
                }
            }
            if(falling) fallGems();
        }

        matches = getMatched();
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

    if(Gem_Matrix[first_x][first_y] != nullptr && Gem_Matrix[second_x][second_y]!= nullptr)
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
    std::vector<std::pair<int,int> > gem_locs;
    int color = Gem_Matrix[second_x][second_y]->getColor();

    for(int y = 0; y < BOARD_HEIGHT; y++)
        for(int x = 0; x < BOARD_WIDTH; x++)
            if(Gem_Matrix[x][y]->getColor() == color)
                gem_locs.push_back(std::make_pair(x,y));

    gem_locs.push_back(std::make_pair(first_x,first_y));
    matches.push_back(Match(gem_locs,true));
    return matches;
}

//Takes a vector of matches that contain the location of all the gems to be removed.
//Returns matches that include the special gem kills and plays the animations
std::vector<Match> GemGrid::fireSpecials(std::vector<Match> matches)
{
    std::vector<std::pair<int,int> > current_gem_locs;
    std::vector<std::pair<int,int> > new_gem_locs;
    for(unsigned int i = 0; i < matches.size(); i++)
    {
        std::vector<std::pair<int,int> > temp_gem_locs = matches[i].getGemLocs();

        for(unsigned int j = 0; j < temp_gem_locs.size(); j++)
        {
            current_gem_locs.push_back(temp_gem_locs[j]);
        }
    }

    for(unsigned int i = 0; i < current_gem_locs.size(); i++)
    {
        int x = current_gem_locs[i].first;
        int y = current_gem_locs[i].second;
        if(Gem_Matrix[x][y]->getType() == 'S' && !Gem_Matrix[x][y]->getActivated())
        {
            std::vector<std::pair<int,int> > temp_gem_locs = Gem_Matrix[x][y]->getKillCoords(x,y);

            for(unsigned int j = 0; j < temp_gem_locs.size(); j++)
                new_gem_locs.push_back(temp_gem_locs[j]);
        }
    }

    if(!new_gem_locs.empty())
    {
        for(unsigned int j = 0; j < current_gem_locs.size(); j++)
        {
            int x = current_gem_locs[j].first;
            int y = current_gem_locs[j].second;
            if(Gem_Matrix[x][y]->getType() == 'S' && !Gem_Matrix[x][y]->getActivated())
                Gem_Matrix[x][y]->setActivated(true);
        }
    }

    bool reset = true;
    while(reset)
    {
        reset = false;
        for(unsigned int i = 0; i < new_gem_locs.size() && !reset; i++)
        {
            for(unsigned int j = 0; j < current_gem_locs.size() && !reset; j++)
            {
                if(new_gem_locs[i] == current_gem_locs[j])
                {
                    new_gem_locs.erase(new_gem_locs.begin() + i);
                    reset = true;
                }
            }
        }
    }
    std::vector<Match> new_matches = matches;
    if(!new_gem_locs.empty())
    {
        new_matches.push_back(Match(new_gem_locs,true));
        new_matches = fireSpecials(new_matches);
    }
    return new_matches;
}


//Takes a vector of pairs that contain the location of all the gems to be removed.
//Removes them with flair.
float GemGrid::removeMatches(std::vector<Match> matches)
{
    float score = 0;

    matches=fireSpecials(matches);

    for(int num = 0; num < ANIM_LENGTH; num++)
    {
        for(unsigned int i = 0; i < matches.size(); i++)
        {
            if(matches[i].getLargeMatch())
                matches[i].printAbsorb(num,Window_1,Gem_Matrix);
            else
                matches[i].printShrink(num,Window_1,Gem_Matrix);
        }
        wrefresh(Window_1);
        usleep((SPEED*60000)/ANIM_LENGTH);
    }
    for(unsigned int i = 0; i < matches.size(); i++)
    {
        if(matches[i].getLargeMatch())
            score += matches[i].replaceWithSpecial(Gem_Matrix);
        else
            score += matches[i].deleteGems(Gem_Matrix);

    }
    for(unsigned int i = 0; i < matches.size(); i++)
    {
        matches[i].printGems(Window_1,Gem_Matrix);
    }
    wrefresh(Window_1);
    usleep(SPEED*30000);
    return score;
}

//Makes the gems fall into blank spaces below them.
void GemGrid::fallGems()
{
    //Loops through the matrix from bottom up, and sets any gems that need to fall, to falling.
    for(int i = grid_height - 1; i > 0; i--)
    {
        for(int j = 0; j < grid_width; j++)
        {
            if(Gem_Matrix[j][i]==nullptr)
            {
                if(Gem_Matrix[j][i-1]!=nullptr) Gem_Matrix[j][i-1]->setFalling(true);
            }
            else if(Gem_Matrix[j][i]->getFalling())
            {
                if(Gem_Matrix[j][i-1]!=nullptr) Gem_Matrix[j][i-1]->setFalling(true);
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
                if(Gem_Matrix[j][i]!=nullptr)
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
            if(Gem_Matrix[j][i] == nullptr)
            {
                if(Gem_Matrix[j][i-1] != nullptr && !Gem_Matrix[j][i-1]->getNew()) //Checks if gem above is present and not new.
                {
                    Gem_Matrix[j][i] = Gem_Matrix[j][i-1];
                    Gem_Matrix[j][i]->setFalling(false);
                    Gem_Matrix[j][i-1] = nullptr;
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
        if(Gem_Matrix[j][0] != nullptr)
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
                    if(Gem_Matrix[x][b_y]!=nullptr)
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
                if(Gem_Matrix[x][b_y]!=nullptr)
                {
                    if(b_y < grid_height-1)
                    {
                        Gem_Matrix[x][b_y+1] = Gem_Matrix[x][b_y];
                        Gem_Matrix[x][b_y] = nullptr;
                    }
                    else
                    {
                        delete Gem_Matrix[x][b_y];
                        Gem_Matrix[x][b_y] = nullptr;
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
            for(int y = grid_height - 1; y > 0; y-- )
            {
                for(int x = 0; x < grid_width; x++)
                {
                    if(Gem_Matrix[x][y]!=nullptr)
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
        for(int y = grid_height - 1; y > 0; y-- )
        {
            for(int x = 0; x < grid_width; x++)
            {
                if(Gem_Matrix[x][y]!=nullptr)
                {
                    if(y < grid_height - 1)
                    {
                        Gem_Matrix[x][y+1] = Gem_Matrix[x][y];
                        Gem_Matrix[x][y] = nullptr;
                    }
                    else
                    {
                        delete Gem_Matrix[x][y];
                        Gem_Matrix[x][y] = nullptr;
                    }
                }
            }
        }
    }
}

void GemGrid::printCursor(int x, int y, const char* cursor)
{
    mvwprintw(Window_1,y*GEM_HEIGHT+2,x*GEM_WIDTH,cursor);
}

void GemGrid::removeCursor(int x, int y)
{
    Gem_Matrix[x][y]->printGem(x*GEM_WIDTH,y*GEM_HEIGHT,Window_1);
}
