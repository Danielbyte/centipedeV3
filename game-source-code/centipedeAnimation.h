#ifndef CENTIPEDEANIMATION_H
#define CENTIPEDEANIMATION_H

#include "Centipede.h"
#include "SfmlDataType.h"
#include "GameDataType.h"

class centipedeAnimation
{
public:
    centipedeAnimation();
    void Animate (shared_ptr<Centipede>&);
    Texture segment_texture;
    Texture head_texture;
    private:
};
#endif // CENTIPEDEANIMATION_H
