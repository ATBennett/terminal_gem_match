#ifndef SHRINK_EFFECT_H
#define SHRINK_EFFECT_H

#include <definitions.h>
#include <Effect.h>
#include <string>
#include <vector>


class ShrinkEffect : public Effect
{
    public:
        ShrinkEffect(int,int,int,WINDOW*);
        virtual ~ShrinkEffect();

        void playEffect() override;
};

#endif // SHRINK_EFFECT_H
