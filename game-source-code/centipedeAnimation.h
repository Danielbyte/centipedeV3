#ifndef CENTIPEDEANIMATION_H
#define CENTIPEDEANIMATION_H

#include "Centipede.h"
#include "gameResources.h"
#include "GameDataType.h"

class centipedeAnimation
{
public:
    centipedeAnimation();
    void Animate (shared_ptr<Centipede>&);
    sf::Texture segment_texture;
    sf::Texture head_texture;
    private:
};
#endif // CENTIPEDEANIMATION_H
