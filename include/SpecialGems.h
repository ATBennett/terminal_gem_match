#ifndef SPECIALGEMS_H
#define SPECIALGEMS_H
#include "Gem.h"

class StarGem : public Gem
{
    public:
        StarGem(int);
        virtual ~StarGem();
        void printGem(int,int, WINDOW*) override;
        std::vector<std::pair<int,int> > getKillCoords(int,int) override;
        Effect* initEffect(int,int,WINDOW*) override;
};

class FireGem : public Gem
{
    public:
        FireGem(int);
        virtual ~FireGem();
        void printGem(int,int, WINDOW*) override;
        std::vector<std::pair<int,int> > getKillCoords(int,int) override;
        Effect* initEffect(int,int,WINDOW*) override;
};

class ColorNukeGem : public Gem
{
    public:
        ColorNukeGem();
        virtual ~ColorNukeGem();
        void printGem(int,int, WINDOW*) override;
};

class StarNukeGem : public Gem
{
    public:
        StarNukeGem(int);
        virtual ~StarNukeGem();
        void printGem(int,int, WINDOW*) override;
        std::vector<std::pair<int,int> > getKillCoords(int,int) override;
        Effect* initEffect(int,int,WINDOW*) override;
};
#endif // SPECIALGEMS_H
