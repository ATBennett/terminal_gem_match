//Implementation of the GemGrid class.

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <algorithm>
#include "../include/GemGrid.h"
#include "../include/ShrinkEffect.h"
#include "../include/SpecialEffects.h"

GemGrid::GemGrid(unsigned int width, unsigned int height, WINDOW* Screen_1)
{
    srand(time(nullptr));
    Window_1 = Screen_1;

    //creates entire grid and sets to to nullptr
    for(unsigned int y = 0; y < height; y++)
    {
        std::vector<Gem*> column;
        for(unsigned int x = 0; x < width; x++)
        {
            column.push_back(nullptr);
        }
        Gem_Matrix.push_back(column);
    }

    //Initialises the colors for ncurses (may move this).
    init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
    init_pair(cfg::color_nuke,COLOR_BLACK,COLOR_BLACK);
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
    for(unsigned int y = 0; y < Gem_Matrix.size(); y++)
    {
        for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
        {
            if(Gem_Matrix[y][x] != nullptr)
            {
                delete Gem_Matrix[y][x];
                Gem_Matrix[y][x] = nullptr;
            }
        }
    }
}

void GemGrid::createRandomGrid()
{
    for(unsigned int y = 0; y < Gem_Matrix.size(); y++)
    {
        for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
        {
            Gem_Matrix[y][x] = randGem();
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
    std::vector<std::vector<Gem*> > Gem_Buffer;
    for(unsigned int y = 0; y < Gem_Matrix.size(); y++)
    {
        std::vector<Gem*> Buffer_Column;
        for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
        {
            if(Gem_Matrix[y][x] == nullptr)
                Buffer_Column.push_back(nullptr);

            else
            {
                Gem_Matrix[y][x]->setNew(true);
                Buffer_Column.push_back(Gem_Matrix[y][x]);
                Gem_Matrix[y][x]=nullptr;
            }
        }
        Gem_Buffer.push_back(Buffer_Column);
    }
    //Loops backwards through the buffer matrix.
    for(int b_y = Gem_Matrix.size() - 1; b_y >= 0; b_y--)
    {
        for(unsigned int x = 0; x < Gem_Matrix[b_y].size(); x++)
        {
            Gem_Matrix[0][x]=Gem_Buffer[b_y][x];
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
    for(unsigned int y = 0; y < Gem_Matrix.size(); y++)
    {
        for(unsigned int x = 0;x < Gem_Matrix[y].size();x ++)
        {
            if(Gem_Matrix[y][x] == nullptr)
            {
                //Creates a gem just to print a gem sized void.
                Gem* Temp_Gem = randGem();
                Temp_Gem->printVoid(x*cfg::gem_width,y*cfg::gem_height,Window_1);
                delete Temp_Gem;
            }
            else if(!Gem_Matrix[y][x]->getNew())
            {
                Gem_Matrix[y][x]->printGem(x*cfg::gem_width,y*cfg::gem_height,Window_1);
            }
            else if(Gem_Matrix[y][x]->getNew())
            {
               Gem_Matrix[y][x]->printVoid(x*cfg::gem_width,y*cfg::gem_height,Window_1);
            }
        }
    }
}

//Returns a vector of pairs that give coordinates of gems that have been matched
std::vector<Match> GemGrid::getMatched()
{
    std::vector<Match> matches;
    std::vector<std::pair<unsigned int,unsigned int> > made_matches_h;
    std::vector<std::pair<unsigned int,unsigned int> > made_matches_v;
    //Loops through the entire matrix top down.
    for(unsigned int y = 0; y<Gem_Matrix.size(); y++)
    {
        for(unsigned int x = 0; x<Gem_Matrix[y].size(); x++)
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
                std::vector<std::pair<unsigned int,unsigned int> > h_matches;
                h_matches = matchH(x,y);
                if(!h_matches.empty())
                {
                    matches.push_back(Match(h_matches));
                    made_matches_h.insert(made_matches_h.end(), h_matches.begin(), h_matches.end());
                }
            }
            if(!skip_v)
            {
                std::vector<std::pair<unsigned int,unsigned int> > v_matches;
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
std::vector<std::pair<unsigned int,unsigned int> > GemGrid::matchH(unsigned int x,unsigned int y)
{
    std::vector<std::pair<unsigned int,unsigned int> > matches_h;
    if(x < Gem_Matrix[0].size() && Gem_Matrix[y][x]!=nullptr)
    {
        bool matching = true;
        for(unsigned int new_x = x; new_x < Gem_Matrix[0].size() && matching; new_x++)
        {
            if(Gem_Matrix[y][new_x] != nullptr)
            {
                if(Gem_Matrix[y][x]->getColor() == Gem_Matrix[y][new_x]->getColor())
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
std::vector<std::pair<unsigned int,unsigned int> > GemGrid::matchV(unsigned int x,unsigned int y)
{
    std::vector<std::pair<unsigned int,unsigned int> > matches_v;
    if(x < Gem_Matrix.size() && Gem_Matrix[y][x]!=nullptr)
    {
        bool matching = true;
        for(unsigned int new_y = y; new_y < Gem_Matrix.size() && matching; new_y++)
        {
            if(Gem_Matrix[new_y][x] != nullptr)
            {
                if(Gem_Matrix[y][x]->getColor() == Gem_Matrix[new_y][x]->getColor())
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
            std::vector<std::pair<unsigned int,unsigned int> > first_match_locs = matches[i].getGemLocs();
            for(int j = i+1; j < num_matches && !found_intersect; j++)
            {
                std::vector<std::pair<unsigned int,unsigned int> > second_match_locs = matches[j].getGemLocs();
                for(unsigned int k = 0; k < first_match_locs.size() && !found_intersect; k++)
                {
                    std::pair<unsigned int,unsigned int> first_gem_loc = first_match_locs[k];
                    for(unsigned int l = 0; l < second_match_locs.size() && !found_intersect; l++)
                    {
                        std::pair<unsigned int,unsigned int> second_gem_loc = second_match_locs[l];
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

float GemGrid::swapGems(unsigned int first_x, unsigned int first_y, char dir)
{
    //Input checking
    if(first_x >= Gem_Matrix[first_y].size() || first_y >= Gem_Matrix.size())
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
            if(first_y < Gem_Matrix.size()-1)
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
            if(first_x < Gem_Matrix[first_y].size() - 1)
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

    if(Gem_Matrix[first_y][first_x] == nullptr || Gem_Matrix[second_y][second_x] == nullptr)
        return 0;

    std::vector<Match> matches;
    if(Gem_Matrix[first_y][first_x]->getType() == 'N')
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
            if(cfg::swap_back)
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
            for(unsigned int x = 0; x < Gem_Matrix[0].size() ; x++)
            {
                if(Gem_Matrix[0][x] == nullptr)
                {
                    falling = true;
                    Gem_Matrix[0][x] = randGem();
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
int GemGrid::swapGemPosition(unsigned int first_x, unsigned int first_y, unsigned int second_x, unsigned int second_y)
{
    // Input checking
    if(first_x >= Gem_Matrix[first_y].size() || first_y >= Gem_Matrix.size() || second_x >=  Gem_Matrix[second_y].size() || second_y >= Gem_Matrix.size())
        return ERR;

    else if(first_x < 0 || first_y < 0 || second_x < 0 || second_y < 0)
        return ERR;

    if(Gem_Matrix[first_y][first_x] != nullptr && Gem_Matrix[second_x][second_y]!= nullptr)
    {
        Gem* Gem_Buffer;
        int vec_y = second_y - first_y;
        int vec_x = second_x - first_x;
        int loop_time = (cfg::gem_height * std::abs(vec_y)) + (cfg::gem_width * std::abs(vec_x));   //
        int sleep_time = (cfg::speed*75000)/loop_time;
        //Swap animation.
        for(int i = 1; i <= loop_time; i++)
        {
            int move_x = i*vec_x;
            int move_y = i*vec_y;
            Gem_Matrix[first_y][first_x]->printVoid(first_x*cfg::gem_width,first_y*cfg::gem_height, Window_1);
            Gem_Matrix[second_y][second_x]->printVoid(second_x*cfg::gem_width,second_y*cfg::gem_height, Window_1);
            Gem_Matrix[second_y][second_x]->printGem(second_x*cfg::gem_width-move_x,second_y*cfg::gem_height-move_y, Window_1);
            Gem_Matrix[first_y][first_x]->printGem(first_x*cfg::gem_width+move_x,first_y*cfg::gem_height+move_y, Window_1);
            wrefresh(Window_1);
            usleep(sleep_time);
        }

        Gem_Buffer = Gem_Matrix[second_y][second_x];
        Gem_Matrix[second_y][second_x] = Gem_Matrix[first_y][first_x];
        Gem_Matrix[first_y][first_x] = Gem_Buffer;
        return 1;
    }
    else
        return ERR;
}

std::vector<Match> GemGrid::color_nuke(int first_x,int first_y,int second_x,int second_y)
{
    std::vector<Match> matches;
    std::vector<std::pair<unsigned int,unsigned int> > gem_locs;
    std::vector<ColorNukeEffect> effects;
    int color = Gem_Matrix[second_y][second_x]->getColor();

    for(int y = 0; y < cfg::board_height; y++)
        for(int x = 0; x < cfg::board_width; x++)
            if(Gem_Matrix[y][x]->getColor() == color)
            {
                gem_locs.push_back(std::make_pair(x,y));
                effects.push_back(ColorNukeEffect(x*cfg::gem_width,y*cfg::gem_height,cfg::anim_frames,Window_1));
            }

    gem_locs.push_back(std::make_pair(first_x,first_y));
    effects.push_back(ColorNukeEffect(first_x*cfg::gem_width,first_y*cfg::gem_height,cfg::anim_frames,Window_1));

    for(int num = 0; num < cfg::anim_frames; num++)
    {
        for(unsigned int i = 0; i < effects.size(); i++)
            effects[i].playEffect();

        wrefresh(Window_1);
        usleep((cfg::speed*100000)/cfg::anim_frames);
    }

    matches.push_back(Match(gem_locs,true));
    return matches;
}

//Takes a vector of matches that contain the location of all the gems to be removed.
//Returns matches that include the special gem kills and plays the animations
std::vector<Match> GemGrid::fireSpecials(std::vector<Match> matches)
{
    std::vector<std::pair<unsigned int,unsigned int> > current_gem_locs;
    std::vector<std::pair<unsigned int,unsigned int> > new_gem_locs;
    std::vector<Effect*> effects;
    for(unsigned int i = 0; i < matches.size(); i++)
    {
        std::vector<std::pair<unsigned int,unsigned int> > temp_gem_locs = matches[i].getGemLocs();

        for(unsigned int j = 0; j < temp_gem_locs.size(); j++)
        {
            current_gem_locs.push_back(temp_gem_locs[j]);
        }
    }

    for(unsigned int i = 0; i < current_gem_locs.size(); i++)
    {
        int x = current_gem_locs[i].first;
        int y = current_gem_locs[i].second;
        if(Gem_Matrix[y][x]->getType() == 'S' && !Gem_Matrix[y][x]->getActivated())
        {
            std::vector<std::pair<int,int> > temp_gem_locs = Gem_Matrix[y][x]->getKillCoords(x,y);
            effects.push_back(Gem_Matrix[y][x]->initEffect(x*cfg::gem_width,y*cfg::gem_height,Window_1));

            for(unsigned int j = 0; j < temp_gem_locs.size(); j++)
                new_gem_locs.push_back(temp_gem_locs[j]);
        }
    }


    if(!new_gem_locs.empty())
    {
        for(int num = 0; num < cfg::anim_frames; num++)
        {
            for(unsigned int i = 0; i < effects.size(); i++)
                effects[i]->playEffect();

            wrefresh(Window_1);
            usleep((cfg::speed*100000)/cfg::anim_frames);
        }

        for(unsigned int i = 0; i < effects.size(); i++)
        {
            delete effects[i];
            effects[i]=nullptr;
        }

        for(unsigned int j = 0; j < current_gem_locs.size(); j++)
        {
            int x = current_gem_locs[j].first;
            int y = current_gem_locs[j].second;
            if(Gem_Matrix[y][x]->getType() == 'S' && !Gem_Matrix[y][x]->getActivated())
                Gem_Matrix[y][x]->setActivated(true);
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

    //Shrinking animation
    std::vector<ShrinkEffect> shrink_effects;
    for(unsigned int i = 0; i < matches.size(); i++)
    {
        if( !matches[i].getLargeMatch() )
        {
            std::vector<std::pair<unsigned int,unsigned int>> gem_locs = matches[i].getGemLocs();
            for(unsigned int j = 0; j < gem_locs.size(); j++)
                shrink_effects.push_back(ShrinkEffect(gem_locs[j].first*cfg::gem_width,gem_locs[j].second*cfg::gem_height,cfg::anim_frames,Window_1));
        }
    }
    for(int num = 0; num < cfg::anim_frames; num++)
    {
        for(unsigned int i = 0; i < matches.size(); i++)
            if(matches[i].getLargeMatch())
                matches[i].printAbsorb(num,Window_1,Gem_Matrix);

        for(unsigned int i = 0; i < shrink_effects.size(); i++)
            shrink_effects[i].playEffect();

        wrefresh(Window_1);
        usleep((cfg::speed*60000)/cfg::anim_frames);
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
    usleep(cfg::speed*30000);
    return score;
}

//Makes the gems fall into blank spaces below them.
void GemGrid::fallGems()
{
    //Loops through the matrix from bottom up, and sets any gems that need to fall, to falling.
    for(unsigned int y = Gem_Matrix.size() - 1; y > 0; y--)
    {
        for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
        {
            if(Gem_Matrix[y][x]==nullptr)
            {
                if(Gem_Matrix[y-1][x]!=nullptr) Gem_Matrix[y-1][x]->setFalling(true);
            }
            else if(Gem_Matrix[y][x]->getFalling())
            {
                if(Gem_Matrix[y-1][x]!=nullptr) Gem_Matrix[y-1][x]->setFalling(true);
            }
        }
    }
    //Plays the falling animation b_y lots of loops.
    bool falling = false;
    for(int k = 1; k <= cfg::gem_height; k++)
    {
        int height = (int) Gem_Matrix.size();
        for(int y = height - 1; y >= 0; y--)
        {
            for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
            {
                if(Gem_Matrix[y][x]!=nullptr)
                {
                    if(Gem_Matrix[y][x]->getFalling() && !Gem_Matrix[y][x]->getNew())
                    {
                        Gem_Matrix[y][x]->printVoid( x*cfg::gem_width, y*cfg::gem_height, Window_1);
                        Gem_Matrix[y][x]->printGem( x*cfg::gem_width, y*cfg::gem_height+k, Window_1);
                        falling = true;
                    }
                    else if(Gem_Matrix[y][x]->getNew())
                    {
                        Gem_Matrix[y][x]->printVoid( x*cfg::gem_width, y*cfg::gem_height, Window_1);
                        Gem_Matrix[y][x]->printGem( x*cfg::gem_width, y*cfg::gem_height+k - 3, Window_1);
                        falling = true;
                    }
                    else Gem_Matrix[y][x]->printGem(x*cfg::gem_width,y*cfg::gem_height, Window_1);
                }
                refresh();
            }
        }
        wrefresh(Window_1);
        if(falling) usleep(cfg::speed*10000);
    }
    //Loops through the matrix from the bottom and shifts gems around in the Gem matrix.
    for(unsigned int y = Gem_Matrix.size() - 1; y > 0; y--) //Doesn't include top row of gems.
    {
        for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
        {
            if(Gem_Matrix[y][x] == nullptr)
            {
                if(Gem_Matrix[y-1][x] != nullptr && !Gem_Matrix[y-1][x]->getNew()) //Checks if gem above is present and not new.
                {
                    Gem_Matrix[y][x] = Gem_Matrix[y-1][x];
                    Gem_Matrix[y][x]->setFalling(false);
                    Gem_Matrix[y-1][x] = nullptr;
                }
            }
            else
            {
                Gem_Matrix[y][x]->setFalling(false);
                Gem_Matrix[y][x]->setNew(false); //If a gem isn't on the top row, makes sure it is set to old.
            }
        }
    }
    //Loops through the top row.
    for(unsigned int x = 0; x < Gem_Matrix[0].size(); x++)
    {
        if(Gem_Matrix[0][x] != nullptr)
        {
            Gem_Matrix[0][x]->setFalling(false);
            Gem_Matrix[0][x]->setNew(false);
        }
    }
}

//Prints all the gems falling off the screen in a fancy animation.
void GemGrid::fallAll()
{
    int height = (int) Gem_Matrix.size();
    for( int y = height - 1; y >= 0; y-- ) //Falls the gems until there are spaces between them all.
    {
        //Plays the falling animation.
        for(int h = 0; h < cfg::gem_height; h++)
        {
            for( int b_y = height - 1; b_y >= y; b_y-- ) //Counts up from bottom to Y.
            {
                for(unsigned int x = 0; x < Gem_Matrix[b_y].size(); x++)
                {
                    if(Gem_Matrix[b_y][x]!=nullptr)
                    {
                        Gem_Matrix[b_y][x]->printVoid(x*cfg::gem_width,b_y*cfg::gem_height+h,Window_1);
                        Gem_Matrix[b_y][x]->printGem(x*cfg::gem_width,b_y*cfg::gem_height+h + 1,Window_1);
                    }
                }
            }
            wrefresh(Window_1);
            usleep(cfg::speed*10000);
        }
        //Moves the gems below y down one.
        for( int b_y = height - 1; b_y >= y; b_y-- ) //Counts up from bottom to Y.
        {
            for(unsigned int x = 0; x < Gem_Matrix[b_y].size(); x++)
            {
                if(Gem_Matrix[b_y][x]!=nullptr)
                {
                    if(b_y < height-1)
                    {
                        Gem_Matrix[b_y+1][x] = Gem_Matrix[b_y][x];
                        Gem_Matrix[b_y][x] = nullptr;
                    }
                    else
                    {
                        delete Gem_Matrix[b_y][x];
                        Gem_Matrix[b_y][x] = nullptr;
                    }
                }
            }
        }
    }
    for(unsigned int i = 1; i < Gem_Matrix.size(); i++) // Keep falling until all the gems are off the board.
    {
        //Plays the falling animation.
        for(int h = 0; h < cfg::gem_height; h++)
        {
            for(unsigned int y = Gem_Matrix.size() - 1; y > 0; y-- )
            {
                for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
                {
                    if(Gem_Matrix[y][x]!=nullptr)
                    {
                        Gem_Matrix[y][x]->printVoid(x*cfg::gem_width,y*cfg::gem_height+h,Window_1);
                        Gem_Matrix[y][x]->printGem(x*cfg::gem_width,y*cfg::gem_height+h + 1,Window_1);
                    }
                }
            }
            wrefresh(Window_1);
            usleep(cfg::speed*10000);
        }
        //Moves all the gems down one.
        for(unsigned int y = Gem_Matrix.size() - 1; y > 0; y-- )
        {
            for(unsigned int x = 0; x < Gem_Matrix[y].size(); x++)
            {
                if(Gem_Matrix[y][x]!=nullptr)
                {
                    if(y < Gem_Matrix.size() - 1)
                    {
                        Gem_Matrix[y+1][x] = Gem_Matrix[y][x];
                        Gem_Matrix[y][x] = nullptr;
                    }
                    else
                    {
                        delete Gem_Matrix[y][x];
                        Gem_Matrix[y][x] = nullptr;
                    }
                }
            }
        }
    }
}

void GemGrid::printCursor(int x_loc, int y_loc, char cursor)
{
    int y = y_loc*cfg::gem_height + cfg::gem_height - 1;
    for(int x = x_loc*cfg::gem_width; x < (x_loc+1)*cfg::gem_width; x++)
    {
        mvwaddch(Window_1,y,x,cursor);
    }
}

void GemGrid::removeCursor(int x, int y)
{
    Gem_Matrix[y][x]->printGem(x*cfg::gem_width,y*cfg::gem_height,Window_1);
}
