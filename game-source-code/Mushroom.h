#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "SfmlDataType.h"
#include "GameDataType.h"
#include "MushroomField.h"

class Mushroom
{
public:
    Mushroom(int, int);

    void set_position(float, float);
    void setMatrix_position(int, int);



private:
    //need an animated sprite for behavior of mushrooms
    //AnimatedSprite main_sprite;
    //float scale;
    float offset;
    float row_pos;
    float col_pos;
    vector2f position;
    Texture mushroom_texture;
    Sprite mushroom_sprite;


};
#endif // MUSHROOM_H
