#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
#include "SfmlDataType.h"
class SpriteAnimation : public Sprite //inherits from Sprite class in sfml library
{
public:
    SpriteAnimation();
    Texture death_texture1;
    Texture death_texture2;
    Texture death_texture3;
    Texture death_texture4;
    Texture death_texture5;
    Texture death_texture6;
private:
    //vector <shared_ptr<Sprite>>

};
#endif // SPRITEANIMATION_H
