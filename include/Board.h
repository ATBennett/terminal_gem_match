#include "BasicGems.h"
#include <vector>

#ifndef BOARD_H
#define BOARD_H


class Board
{
    private:
        Gem *GemBoard[100][100];

        Gem* RandGem();
        void fallBoard();
        void printExtras();
        void createSpecial(std::vector<std::pair<int,int> >);
        void matchL(int,int);
        void match4H(int,int);
        void match4V(int,int);
        void match5H(int,int);
        void match5V(int,int);
        void match6H(int,int);
        void match6V(int,int);

        int boardWidth;
        int boardHeight;
        int turns;
        float score;
        int cx;
        int cy;
        bool highlight;
        int speed;
    public:
        Board(int, int);
        virtual ~Board();

        int getTurns();
        void setTurns(int);
        void setCursor(int,int);
        std::pair<int,int> getCursor();
        void mvCursorH(int);
        void mvCursorV(int);
        void printBoard();
        void setHighlight(bool);
        std::vector<std::pair<int,int> > matched();
        void fancyRemoveMatched(std::vector<std::pair<int,int> >);
        void quickRemoveMatched(std::vector<std::pair<int,int> >);
        bool swapGems(std::pair<int,int>,char);
        void printEnd();
};

#endif // BOARD_H
