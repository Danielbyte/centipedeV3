#include "SfmlDataType.h"
#include "GameDataType.h"
#include "Player.h"
#include "MushroomField.h"
#include "CentipedeHead.h"

#ifndef COLLISION_H
#define COLLISION_H
class Collision
{
public:
    Collision();
    bool CheckCollision(vector2d, float, vector2d, float);
    bool isCollidedWithBullet(vector2d, float, vector2d, float);
};
#endif // COLLISION_H

