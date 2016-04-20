#ifndef MATCH_H
#define MATCH_H

#include <vector>


class Match
{
    private:
        std::vector<std::pair<int,int> > gem_locs;
        char type;
    protected:
    public:
        Match(std::vector<std::pair<int,int> >);
        virtual ~Match();

        //Getters and setters
        std::vector<std::pair<int,int> > getGemLocs() { return gem_locs; }
        char getType() { return type; }
};

#endif // MATCH_H
