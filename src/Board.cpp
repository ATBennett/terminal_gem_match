#include <iostream>
#include <ncurses.h>
#include <unistd.h>
//Implementation of the Board class

#include <algorithm>
#include "../include/Board.h"

#define GemSize 3
#define speed 2

Board::Board(int width, int height){
    srand(time(NULL));
    //Populates the board with random gems
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            GemBoard[j][i]=RandGem();
            GemBoard[j][i]->setOld();
        }
    }
    boardHeight = height;
    boardWidth = width;
    highlight = false;
    score = 0;
    turns = 0;
    cx = 0;
    cy = 0;
    //Initialises the colors for ncurses (may move this)
    init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
    init_pair(COLOR_BLUE,COLOR_BLACK,COLOR_BLUE);
    init_pair(COLOR_CYAN,COLOR_BLACK,COLOR_CYAN);
    init_pair(COLOR_GREEN,COLOR_BLACK,COLOR_GREEN);
    init_pair(COLOR_MAGENTA,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(COLOR_RED,COLOR_BLACK,COLOR_RED);
    init_pair(COLOR_WHITE,COLOR_BLACK,COLOR_WHITE);
    init_pair(COLOR_YELLOW,COLOR_BLACK,COLOR_YELLOW);
}

Board::~Board(){
    //dtor
}

//Creates a new random gem and returns a pointer to it
Gem* Board::RandGem(){
    int randNum = rand() % 7;
    switch(randNum)
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

//Loops through and tells each gem to print itself onto the board
void Board::printBoard(){
    for(int i = 0;i < boardHeight;i ++)
    {
        for(int j = 0; j < boardWidth; j++)
        {
            if(GemBoard[j][i] != NULL){
                if(!GemBoard[j][i]->getIfNew()) GemBoard[j][i]->printGem(j*GemSize*2,i*GemSize);
            }
        }
    }
    printExtras();
}

void Board::setHighlight(bool nHighlight){
    highlight = nHighlight;
    return;
}

void Board::setCursor(int x, int y){
    if(cx > boardWidth - 1) cx = boardWidth - 1;
    else cx = x;
    if(cy > boardHeight - 1) cy = boardHeight - 1;
    else cy = y;
    return;
}

void Board::mvCursorH(int amount){
    cx = cx + amount;
    if(cx >= boardWidth - 1) cx = boardWidth - 1;
    else if(cx < 0) cx = 0;
    return;
}

void Board::mvCursorV(int amount){
    cy = cy + amount;
    if(cy >= boardHeight - 1) cy = boardHeight - 1;
    else if(cy < 0) cy = 0;
    return;
}

void Board::setTurns(int nTurns){
    turns = nTurns;
    return;
}

int Board::getTurns(){
    return turns;
}

//Returns a vector of pairs that give coordinates of gems that have been matched
std::vector<std::pair<int,int> > Board::matched(){
    std::vector<std::pair<int,int> > GemLocs;
    //Loops through the entire board top down
    for(int i = 0; i<boardHeight; i++){
        for(int j = 0; j<boardWidth; j++){

            //Horizontal matches
            if(j < boardWidth - 2 && GemBoard[j][i] != NULL){   //Makes sure to ignore gems too close to the right edge to match
                bool match = true;
                int matchLength = 1;
                while(match && j+matchLength < boardWidth){     //Makes sure not to go out of bounds
                    if(GemBoard[j+matchLength][i] != NULL){     //Avoids null pointers
                        if(GemBoard[j][i]->getColor() == GemBoard[j+matchLength][i]->getColor()) matchLength++;
                        else match = false;
                    }
                    else match = false;
                }

                if(matchLength >= 3){
                    for(int k = 0; k<matchLength; k++){ //From leftmost gem in a horizontal match, loops through
                            GemLocs.push_back(std::make_pair(j+k,i));
                    }
                }
            }

            //Verticle matches
            if(i < boardHeight - 2 && GemBoard[j][i] != NULL){  //Makes sure to ignore gems too close to the bottom edge to match
                int matchLength = 1;
                bool match = true;
                while(match && i+matchLength < boardHeight){    //Makes sure not to go out of bounds
                    if(GemBoard[j][i+matchLength] != NULL){     //Avoids null pointers
                        if(GemBoard[j][i]->getColor() == GemBoard[j][i+matchLength]->getColor()) matchLength++;
                        else match = false;
                    }
                    else match = false;
                }

                if(matchLength >= 3){
                    for(int k = 0; k<matchLength; k++){ //From topmost gem in a verticle match, loops through
                        GemLocs.push_back(std::make_pair(j,i+k));
                    }
                }
            }

        }
    }

    //Removes duplicates
    std::sort(GemLocs.begin(),GemLocs.end());
    GemLocs.erase(std::unique (GemLocs.begin(), GemLocs.end()), GemLocs.end());

    return GemLocs;
}

//Quickly swaps all matched gems for randomly generated ones
void Board::quickRemoveMatched(std::vector<std::pair<int,int> > GemLocs){
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        delete GemBoard[x][y];
        GemBoard[x][y] = RandGem();
        GemBoard[x][y]->setOld();
    }
}

//Swaps the position of 2 Gem pointers
//Returns false if this was not possible
bool Board::swapGems(std::pair<int,int> location, char direction){
    std::pair<int,int> dVector;
    Gem* GemBuffer;
    if(direction == 'U'){
        if(location.second <= 0) return false;
        else{
            dVector.first=0;
            dVector.second=-1;
        }
    }
    else if(direction == 'D'){
        if(location.second >= boardHeight-1) return false;
        else{
            dVector.first=0;
            dVector.second=1;
        }
    }
    else if(direction == 'L'){
        if(location.first <= 0) return false;
        else{
            dVector.first=-1;
            dVector.second=0;
        }
    }
    else if(direction == 'R'){
        if(location.first >= boardWidth - 1) return false;
        else{
            dVector.first=1;
            dVector.second=0;
        }
    }
    else return false;
    GemBuffer = GemBoard[location.first + dVector.first][location.second + dVector.second];
    GemBoard[location.first + dVector.first][location.second + dVector.second] = GemBoard[location.first][location.second];
    GemBoard[location.first][location.second] = GemBuffer;
    return true;
}

std::pair<int,int> Board::getCursor(){
    return std::make_pair(cx,cy);
}

//Finds the matches larger than 3 and runs the corresponding function
//WIP
void Board::createSpecial(std::vector<std::pair<int,int> > GemLocs){
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        bool doNothingH = false;
        bool doNothingV = false;
        int matchH = 0;
        int matchV = 0;
        int currX = GemLocs[i].first;
        int currY = GemLocs[i].second;
        for(unsigned int j = 0; j< GemLocs.size(); j++){
            int newX = GemLocs[j].first;
            int newY = GemLocs[j].second;
            if(GemBoard[currX][currY]->getColor()==GemBoard[newX][newY]->getColor()){
                if(newY == currY && newX == currX - 1) doNothingH = true;
                if(newX == currX && newY == currY - 1) doNothingV = true;
                if(!doNothingH && newY == currY){
                    if(newX - currX > matchH) matchH = newX - currX;
                }
                if(!doNothingV && newX == currX){
                    if(newY - currY > matchV) matchV = newY - currY;
                }
            }
        }
        if(!doNothingH){
            if(matchH == 3 && matchV == 3) matchL(currX,currY);
            else if(matchH == 4) match4H(currX,currY);
            else if(matchH == 5) match5H(currX,currY);
            else if(matchH == 6) match6H(currX,currY);
        }
        if(!doNothingV){
            if(matchV == 4) match4V(currX, currY);
            if(matchV == 5) match5V(currX, currY);
            if(matchV == 6) match6V(currX, currY);
        }
    }
    return;
}

//Takes a vector of pairs that contain the location of all the gems to be removed
//Removes them with flair
void Board::fancyRemoveMatched(std::vector<std::pair<int,int> > GemLocs){
    clear();
    printBoard();
    //Prints first shrink
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        GemBoard[x][y]->printVoid(x*GemSize*2,y*GemSize);
        GemBoard[x][y]->printShrink1(x*GemSize*2,y*GemSize);
    }
    refresh();
    usleep(speed*25000);
    //Prints second shrink
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        GemBoard[x][y]->printVoid(x*GemSize*2,y*GemSize);
        GemBoard[x][y]->printShrink2(x*GemSize*2,y*GemSize);
    }
    refresh();
    usleep(speed*25000);
    float rawScore = 0;
    float multiplier = 0;
    //Removes matched gems and adds onto the score
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        rawScore += GemBoard[x][y]->getScore();
        multiplier += 0.33333333;
        delete GemBoard[x][y];  //Makes sure the object is deleted
        GemBoard[x][y] = NULL;  //Sets the pointer to null
    }
    score = score + (rawScore * multiplier);
    fallBoard();
    return;
}

//Makes the gems fall into blank spaces below them
void Board::fallBoard(){
    bool falling = true;
    while(falling){
        falling = false;
        //Loops through the board from bottom up, and sets any gems that need to fall, falling
        for(int i = boardHeight - 1; i > 0; i--){
            for(int j = 0; j < boardWidth; j++){
                if(GemBoard[j][i]==NULL){
                    falling = true;
                    if(GemBoard[j][i-1]!=NULL) GemBoard[j][i-1]->setFalling(true);
                }
                else if(GemBoard[j][i]->getFalling()&&GemBoard[j][i-1]!=NULL){
                    GemBoard[j][i-1]->setFalling(true);
                }
            }
        }
        //Plays the falling animation by lots of loops
        for(int k = 1; k < GemSize; k++){
            clear();
            for(int i = boardHeight - 1; i >= 0; i--){
                for(int j = 0; j < boardWidth; j++){
                    if(GemBoard[j][i]!=NULL){
                        if(GemBoard[j][i]->getFalling() && !GemBoard[j][i]->getIfNew()) GemBoard[j][i]->printGem(j*2*GemSize,i*GemSize+k);
                        else if(GemBoard[j][i]->getIfNew()){
                            GemBoard[j][i]->printGem(j*2*GemSize,i*GemSize+k - 3);
                        }
                        else GemBoard[j][i]->printGem(j*2*GemSize,i*GemSize);
                    }
                }
            }
            printExtras();
            refresh();
            usleep(speed*25000);
        }
        //Loops through the board from the bottom and shifts gems around in the Gem pointer matrix
        for(int i = boardHeight - 1; i > 0; i--){ //Doesn't include top row of gems
            for(int j = 0; j < boardWidth; j++){
                if(GemBoard[j][i] == NULL){
                    if(GemBoard[j][i-1] != NULL && !GemBoard[j][i-1]->getIfNew()){ //Checks if gem above is present and not new
                        GemBoard[j][i] = GemBoard[j][i-1];
                        GemBoard[j][i]->setFalling(false);
                        GemBoard[j][i-1] = NULL;
                    }
                }
                else{
                    GemBoard[j][i]->setFalling(false);
                    GemBoard[j][i]->setOld(); //If a gem isn't on the top row, makes sure it is set to old
                }
            }
        }
        // Loops through the top row
        for(int j = 0; j < boardWidth; j++){
            if(GemBoard[j][0] != NULL){
                GemBoard[j][0]->setFalling(false);
                GemBoard[j][0]->setOld();
            }
            else{
                GemBoard[j][0] = RandGem(); // If a gem is not present this creates a new one
                falling = true;             // sets it to falling (not sure why this is here)
            }
        }
        clear();
        printBoard();
        refresh();
        usleep(speed*25000);
    }
    return;
}

//Prints all the extra bits around the board (May seperate)
void Board::printExtras(){
    attron(COLOR_PAIR(COLOR_BLACK));
    if(highlight) mvprintw(cy*GemSize+2,cx*2*GemSize,"++++++"); //Highlight changes the cursor
    else mvprintw(cy*GemSize+2,cx*2*GemSize,"======");
    attroff(COLOR_PAIR(COLOR_BLACK));
    mvprintw(10,boardWidth*2*GemSize + 4,"Score: %.0f",score);
    mvprintw(11,boardWidth*2*GemSize + 4,"Turns Remaining: %d",turns);
    mvprintw(1,boardWidth*2*GemSize + 4,"Controls: ");
    mvprintw(3,boardWidth*2*GemSize + 4,"Arrow keys: move cursor");
    mvprintw(5,boardWidth*2*GemSize + 4,"Space bar: select Gem");
    mvprintw(7,boardWidth*2*GemSize + 4,"You must make a match");
    mvprintw(8,boardWidth*2*GemSize + 4,"for a move to be valid");
    return;
}

//At the moment prints the gems falling then the score
//Currently broken
void Board::printEnd(){
    printBoard();   //Not sure why this is here
    usleep(speed*25000);
    for(int i = 0; i < boardHeight; i++){
        clear();
        for(int y = 0; y < boardHeight; y++){
            for(int x = 0; x < boardWidth; x++){
                if(i+y < boardHeight){
                    attron(COLOR_PAIR(GemBoard[x][y]->getColor()));
                    mvprintw((i*2)+y*2+1,x*4,"    ");
                    mvprintw((i*2)+y*2+2,x*4,"    ");
                    attroff(COLOR_PAIR(GemBoard[x][y]->getColor()));
                }
            }
        }
        refresh();
        usleep(speed*25000);
        clear();
        for(int y = 0; y < boardHeight; y++){
            for(int x = 0; x < boardWidth; x++){
                if(i+y < boardHeight){
                    attron(COLOR_PAIR(GemBoard[x][y]->getColor()));
                    mvprintw((i*2)+y*2+2,x*4,"    ");
                    mvprintw((i*2)+y*2+3,x*4,"    ");
                    attroff(COLOR_PAIR(GemBoard[x][y]->getColor()));
                }
            }
        }
        refresh();
    }
    clear();
    mvprintw(0,0,"Your score: %.0f",score);
    refresh();
    sleep(5);
    return;
}

// Not implemented yet
void Board::matchL(int x, int y){}
void Board::match4H(int x, int y){}
void Board::match4V(int x, int y){}
void Board::match5H(int x, int y){}
void Board::match5V(int x, int y){}
void Board::match6H(int x, int y){}
void Board::match6V(int x, int y){}
