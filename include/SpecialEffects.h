#ifndef SPECIALEFFECTS_H
#define SPECIALEFFECTS_H

#include "Effect.h"


class ExplosionEffect : public Effect
{
    public:
        ExplosionEffect(int,int,int,WINDOW*);
        virtual ~ExplosionEffect();

        void playEffect() override;
};

class LightningEffect : public Effect
{
    public:
        LightningEffect(int,int,int,WINDOW*);
        virtual ~LightningEffect();

        void playEffect() override;
};

class ColorNukeEffect : public Effect
{
    public:
        ColorNukeEffect(int,int,int,WINDOW*);
        virtual ~ColorNukeEffect();

        void playEffect() override;
};

class StarNukeEffect : public Effect
{
    public:
        StarNukeEffect(int,int,int,WINDOW*);
        virtual ~StarNukeEffect();

        void playEffect() override;
};
#endif // SPECIALEFFECTS_H
