#include "Collision.h"

Collision::Collision(){}

bool Collision::CheckCollision(vector2d obj1Pos, float object1Size, vector2d obj2Pos, float object2Size)
{

    auto PlayerLeftSide = obj1Pos.x;
    auto PlayerRightSide = PlayerLeftSide + object1Size;
    auto PlayerTopSide = obj1Pos.y;
    auto PlayerBottomSide = PlayerTopSide + object1Size;

    auto mushLeftSide = obj2Pos.x;
    auto mushRightSide = mushLeftSide + object2Size;
    auto mushTopSide = obj2Pos.y;
    auto mushBottomSide = mushTopSide + object2Size;

    if(PlayerRightSide > mushLeftSide && PlayerLeftSide < mushRightSide &&
       PlayerBottomSide > mushTopSide && PlayerTopSide < mushBottomSide)
    {
        return true;
    }

    else
        return false;
}

bool Collision::isCollidedWithBullet(vector2d bulletPos, float bulletSize, vector2d objectPos, float objectSize)
{
    float objecOrigin = objectSize/2;

    float X_bulletPos = bulletPos.x;
    float Y_bulletPos = bulletPos.y;

    float X_objectPos = objectPos.x;
    float Y_objectPos = objectPos.y;

    if((X_bulletPos >= (X_objectPos - objecOrigin)) && (X_bulletPos <= (X_objectPos + objecOrigin))
       && (Y_bulletPos >= (Y_objectPos - objecOrigin)) && (Y_bulletPos <= (Y_objectPos + objecOrigin)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
