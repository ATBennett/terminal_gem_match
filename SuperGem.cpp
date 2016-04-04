#include "SuperGem.h"

SuperGem::SuperGem(int nColour, int nScore, char nType)
: Gem(nColour, nScore)
{
    setType(nType);
}

SuperGem::~SuperGem()
{
    //dtor
}
