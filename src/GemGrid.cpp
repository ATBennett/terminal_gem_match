#include <iostream>
#include <ncurses.h>
#include <unistd.h>
//Implementation of the GemGrid class

#include <algorithm>
#include "../include/GemGrid.h"

GemGrid::GemGrid(unsigned int width, unsigned int height, WINDOW *screen1){
    srand(time(NULL));
    gridHeight = height;
    gridWidth = width;
    window1 = screen1;

    //Initialises the colors for ncurses (may move this)

    init_pair(COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
    init_pair(COLOR_BLUE,COLOR_WHITE,COLOR_BLUE);
    init_pair(COLOR_CYAN,COLOR_BLACK,COLOR_CYAN);
    init_pair(COLOR_GREEN,COLOR_BLACK,COLOR_GREEN);
    init_pair(COLOR_MAGENTA,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(COLOR_RED,COLOR_BLACK,COLOR_RED);
    init_pair(COLOR_WHITE,COLOR_BLACK,COLOR_WHITE);
    init_pair(COLOR_YELLOW,COLOR_BLACK,COLOR_YELLOW);
}

GemGrid::~GemGrid(){
    //dtor
}

void GemGrid::createRandomGrid(){
    for(int i = 0; i < gridHeight; i++)
    {
        for(int j = 0; j < gridWidth; j++)
        {
            GemMatrix[j][i]=RandGem();
        }
    }
    while(!matched().empty()){
        quickRemoveMatched(matched());
    }
}

//Animation to make gems appear as if they are falling onto the board
void GemGrid::fallOntoBoard(){
    Gem *GemBuffer[100][100];
    for(int y = 0; y < gridHeight; y++){
        for(int x = 0; x < gridWidth; x++){
            GemBuffer[x][y]=GemMatrix[x][y];
            GemBuffer[x][y]->setNew(true);
            GemMatrix[x][y]=NULL;
        }
    }
    for(int bY = gridHeight - 1; bY >= 0; bY--){ //loops backwards through the buffer matrix
        for(int x = 0; x < gridWidth; x++){
            GemMatrix[x][0]=GemBuffer[x][bY];
        }
        fallGems();
        if(bY != 0) fallGems();
    }
}

//Creates a new random gem and returns a pointer to it
Gem* GemGrid::RandGem(){
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

//Loops through and tells each gem to print itself onto the terminal
void GemGrid::printGrid(){
    for(int i = 0;i < gridHeight;i ++)
    {
        for(int j = 0; j < gridWidth; j++)
        {
            if(GemMatrix[j][i] != NULL){
                if(!GemMatrix[j][i]->getNew()) GemMatrix[j][i]->printGem(j*GemWidth,i*GemHeight,window1);
            }
        }
    }
}

//Returns a vector of pairs that give coordinates of gems that have been matched
std::vector<std::pair<int,int> > GemGrid::matched(){
    std::vector<std::pair<int,int> > GemLocs;
    //Loops through the entire matrix top down
    for(int i = 0; i<gridHeight; i++){
        for(int j = 0; j<gridWidth; j++){

            //Horizontal matches
            if(j < gridWidth - 2 && GemMatrix[j][i] != NULL){   //Makes sure to ignore gems too close to the right edge to match
                bool match = true;
                int matchLength = 1;
                while(match && j+matchLength < gridWidth){     //Makes sure not to go out of bounds
                    if(GemMatrix[j+matchLength][i] != NULL){     //Avoids null pointers
                        if(GemMatrix[j][i]->getColor() == GemMatrix[j+matchLength][i]->getColor()) matchLength++;
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
            if(i < gridHeight - 2 && GemMatrix[j][i] != NULL){  //Makes sure to ignore gems too close to the bottom edge to match
                int matchLength = 1;
                bool match = true;
                while(match && i+matchLength < gridHeight){    //Makes sure not to go out of bounds
                    if(GemMatrix[j][i+matchLength] != NULL){     //Avoids null pointers
                        if(GemMatrix[j][i]->getColor() == GemMatrix[j][i+matchLength]->getColor()) matchLength++;
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
void GemGrid::quickRemoveMatched(std::vector<std::pair<int,int> > GemLocs){
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        delete GemMatrix[x][y];
        GemMatrix[x][y] = RandGem();
    }
}

//Swaps the position of 2 Gem pointers
//Returns false if this was not possible
bool GemGrid::swapGems(std::pair<int,int> location, char direction){
    std::pair<int,int> dVector;
    Gem* GemBuffer;
    int firstx = location.first;
    int firsty = location.second;
    if(direction == 'U'){
        if(location.second <= 0) return false;
        else{
            dVector.first=0;
            dVector.second=-1;
        }
    }
    else if(direction == 'D'){
        if(location.second >= gridHeight-1) return false;
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
        if(location.first >= gridWidth - 1) return false;
        else{
            dVector.first=1;
            dVector.second=0;
        }
    }
    else return false;
    int secondx = firstx + dVector.first;
    int secondy = firsty + dVector.second;
    if(GemMatrix[firstx][firsty] != NULL && GemMatrix[secondx][secondy]!= NULL){
        int loopTime = (GemHeight * std::abs(dVector.second)) + (GemWidth * std::abs(dVector.first));
        int sleepTime = (Speed*75000)/loopTime;
        //Swap animation
        for(int i = 1; i <= loopTime; i++){
            int moveX = i*dVector.first;
            int moveY = i*dVector.second;
            GemMatrix[firstx][firsty]->printVoid(firstx*GemWidth,firsty*GemHeight, window1);
            GemMatrix[secondx][secondy]->printVoid(secondx*GemWidth,secondy*GemHeight, window1);
            GemMatrix[secondx][secondy]->printGem(secondx*GemWidth-moveX,secondy*GemHeight-moveY, window1);
            GemMatrix[firstx][firsty]->printGem(firstx*GemWidth+moveX,firsty*GemHeight+moveY, window1);
            wrefresh(window1);
            usleep(sleepTime);
        }

        GemBuffer = GemMatrix[secondx][secondy];
        GemMatrix[secondx][secondy] = GemMatrix[firstx][firsty];
        GemMatrix[firstx][firsty] = GemBuffer;
        return true;
    }
    else return false;
}

//Finds the matches larger than 3 and runs the corresponding function
//WIP
void GemGrid::createSpecial(std::vector<std::pair<int,int> > GemLocs){
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
            if(GemMatrix[currX][currY]->getColor()==GemMatrix[newX][newY]->getColor()){
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
float GemGrid::fancyRemoveMatched(std::vector<std::pair<int,int> > GemLocs){
    printGrid();
    //Prints first shrink
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        GemMatrix[x][y]->printVoid( x*GemWidth, y*GemHeight, window1);
        GemMatrix[x][y]->printShrink1( x*GemWidth, y*GemHeight, window1);
    }
    wrefresh(window1);
    usleep(Speed*30000);
    //Prints second shrink
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        GemMatrix[x][y]->printVoid(x*GemWidth, y*GemHeight, window1);
        GemMatrix[x][y]->printShrink2(x*GemWidth, y*GemHeight, window1);
    }
    wrefresh(window1);
    usleep(Speed*30000);
    //Prints a void where a gem used to be
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        GemMatrix[x][y]->printVoid(x*GemWidth, y*GemHeight, window1);
    }
    wrefresh(window1);
    usleep(Speed*30000);
    float rawScore = 0;
    float multiplier = 0;
    //Removes matched gems and adds onto the score
    for(unsigned int i = 0; i < GemLocs.size(); i++){
        int x = GemLocs[i].first;
        int y = GemLocs[i].second;
        rawScore += GemMatrix[x][y]->getScore();
        multiplier += 0.33333333;
        delete GemMatrix[x][y];  //Makes sure the object is deleted
        GemMatrix[x][y] = NULL;  //Sets the pointer to null
    }

    //Falls gems down and adds new random ones at the top
    bool falling = true;
    while(falling){
        falling = false;
        fallGems();
        for(int x = 0; x < gridWidth; x++){
            if( GemMatrix[x][0] == NULL ) {
                falling = true;
                GemMatrix[x][0] = RandGem();
            }
        }
        if(falling) fallGems();
    }
    return rawScore * multiplier;
}

//Makes the gems fall into blank spaces below them
void GemGrid::fallGems(){
    //Loops through the matrix from bottom up, and sets any gems that need to fall, falling
    for(int i = gridHeight - 1; i > 0; i--){
        for(int j = 0; j < gridWidth; j++){
            if(GemMatrix[j][i]==NULL){
                if(GemMatrix[j][i-1]!=NULL) GemMatrix[j][i-1]->setFalling(true);
            }
            else if(GemMatrix[j][i]->getFalling()){
                if(GemMatrix[j][i-1]!=NULL) GemMatrix[j][i-1]->setFalling(true);
            }
        }
    }
    //Plays the falling animation by lots of loops
    bool falling = false;
    for(int k = 1; k <= GemHeight; k++){
        for(int i = gridHeight - 1; i >= 0; i--){
            for(int j = 0; j < gridWidth; j++){
                if(GemMatrix[j][i]!=NULL){
                    if(GemMatrix[j][i]->getFalling() && !GemMatrix[j][i]->getNew()){
                        GemMatrix[j][i]->printVoid( j*GemWidth, i*GemHeight, window1);
                        GemMatrix[j][i]->printGem( j*GemWidth, i*GemHeight+k, window1);
                        falling = true;
                    }
                    else if(GemMatrix[j][i]->getNew()){
                        GemMatrix[j][i]->printVoid( j*GemWidth, i*GemHeight, window1);
                        GemMatrix[j][i]->printGem( j*GemWidth, i*GemHeight+k - 3, window1);
                        falling = true;
                    }
                    else GemMatrix[j][i]->printGem(j*GemWidth,i*GemHeight, window1);
                }
            }
        }
        wrefresh(window1);
        if(falling) usleep(Speed*20000);
    }
    //Loops through the matrix from the bottom and shifts gems around in the Gem matrix
    for(int i = gridHeight - 1; i > 0; i--){ //Doesn't include top row of gems
        for(int j = 0; j < gridWidth; j++){
            if(GemMatrix[j][i] == NULL){
                if(GemMatrix[j][i-1] != NULL && !GemMatrix[j][i-1]->getNew()){ //Checks if gem above is present and not new
                    GemMatrix[j][i] = GemMatrix[j][i-1];
                    GemMatrix[j][i]->setFalling(false);
                    GemMatrix[j][i-1] = NULL;
                }
            }
            else{
                GemMatrix[j][i]->setFalling(false);
                GemMatrix[j][i]->setNew(false); //If a gem isn't on the top row, makes sure it is set to old
            }
        }
    }
    // Loops through the top row
    for(int j = 0; j < gridWidth; j++){
        if(GemMatrix[j][0] != NULL){
            GemMatrix[j][0]->setFalling(false);
            GemMatrix[j][0]->setNew(false);
        }
    }
}

//Prints all the gems falling off the screen in a fancy animation
void GemGrid::fallAll(){
    for( int y = gridHeight - 1; y >= 0; y-- ){ //Falls the gems until there are spaces between them all
        //Plays the falling animation
        for(int h = 0; h < GemHeight; h++){
            for(int bY = gridHeight - 1; bY >= y; bY-- ) { //Counts up from bottom to Y
                for(int x = 0; x < gridWidth; x++){
                    if(GemMatrix[x][bY]!=NULL){
                        GemMatrix[x][bY]->printVoid(x*GemWidth,bY*GemHeight+h,window1);
                        GemMatrix[x][bY]->printGem(x*GemWidth,bY*GemHeight+h + 1,window1);
                    }
                }
            }
            wrefresh(window1);
            usleep(Speed*15000);
        }
        //Moves the gems below y down one
        for(int bY = gridHeight - 1; bY >= y; bY-- ) { //Counts up from bottom to Y
            for(int x = 0; x < gridWidth; x++){
                if(GemMatrix[x][bY]!=NULL){
                    if(bY < gridHeight){
                        GemMatrix[x][bY+1] = GemMatrix[x][bY];
                        GemMatrix[x][bY] = NULL;
                    }
                    else{
                        delete GemMatrix[x][bY];
                        GemMatrix[x][bY] = NULL;
                    }
                }
            }
        }
    }
    for(int i = 1; i < gridHeight; i++){ // Keep falling until all the gems are off the board
        //plays the falling animation
        for(int h = 0; h < GemHeight; h++){
            for(int y = gridHeight - 1; y >= 0; y-- ) {
                for(int x = 0; x < gridWidth; x++){
                    if(GemMatrix[x][y]!=NULL){
                        GemMatrix[x][y]->printVoid(x*GemWidth,y*GemHeight+h,window1);
                        GemMatrix[x][y]->printGem(x*GemWidth,y*GemHeight+h + 1,window1);
                    }
                }
            }
            wrefresh(window1);
            usleep(Speed*15000);
        }
        //Moves all the gems down one
        for(int y = gridHeight - 1; y >= 0; y-- ) {
            for(int x = 0; x < gridWidth; x++){
                if(GemMatrix[x][y]!=NULL){
                    if(y < gridHeight){
                        GemMatrix[x][y+1] = GemMatrix[x][y];
                        GemMatrix[x][y] = NULL;
                    }
                    else{
                        delete GemMatrix[x][y];
                        GemMatrix[x][y] = NULL;
                    }
                }
            }
        }
    }
}

// Not implemented yet
void GemGrid::matchL(int x, int y){}
void GemGrid::match4H(int x, int y){}
void GemGrid::match4V(int x, int y){}
void GemGrid::match5H(int x, int y){}
void GemGrid::match5V(int x, int y){}
void GemGrid::match6H(int x, int y){}
void GemGrid::match6V(int x, int y){}
