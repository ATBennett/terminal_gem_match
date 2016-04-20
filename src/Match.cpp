#include "../include/Match.h"

Match::Match(std::vector<std::pair<int,int> > gem_locs_in)
{
    gem_locs = gem_locs_in;
    type = 'R';
}

Match::~Match()
{
    //dtor
}
