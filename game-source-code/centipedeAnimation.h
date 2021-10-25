#ifndef CENTIPEDEANIMATION_H
#define CENTIPEDEANIMATION_H

#include "Centipede.h"
#include "SfmlDataType.h"
#include "GameDataType.h"

class centipedeAnimation
{
public:
    centipedeAnimation(){};
    void Animate (shared_ptr<Centipede>&, shared_ptr<Sprite>&);
    Texture segment_texture;
    private:
};
#endif // CENTIPEDEANIMATION_H
