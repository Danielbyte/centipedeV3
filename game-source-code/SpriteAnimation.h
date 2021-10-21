#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
#include "SfmlDataType.h"
class SpriteAnimation : public Sprite //inherits from Sprite class in sfml library
{
public:
    //SpriteAnimation(){};

    //initialization list
    SpriteAnimation(Texture& texture, int frameCountWidth, int frameCountHeight, float framesPerSecond = 60,
                    int initialFrame = 0, int lastFrame = 0, bool isAnimated = true, bool isLooped = true);

    ~SpriteAnimation(){};


private:

};
#endif // SPRITEANIMATION_H
