#include "Collision.h"

Collision::Collision(){}

bool Collision::CheckCollision(vector2d obj1Pos, float object1Size, vector2d obj2Pos, float object2Size)
{
   /* auto object1Origin = object1Size/2.0f;
    auto Object2Origin = object2Size/2.0f;

    auto object1_X1Pos = obj1Pos.x - object1Origin;
    auto object1_Y1Pos = obj1Pos.y - object1Origin;
    auto object1_X2Pos = obj1Pos.x + object1Origin;
    auto object1_Y2Pos = obj1Pos.y + object1Origin;

    auto object2_X1Pos = obj2Pos.x + Object2Origin;
    auto object2_Y1Pos = obj2Pos.y + Object2Origin;
    auto object2_X2Pos = obj2Pos.x - Object2Origin;
    auto object2_Y2Pos = obj2Pos.y - Object2Origin;

    if((object2_X1Pos >= object1_X1Pos && object2_X1Pos <= object1_X2Pos && object2_Y1Pos >= object1_Y1Pos && object2_Y1Pos <= object1_Y2Pos) ||
    (object2_X1Pos >= object1_X1Pos && object2_X1Pos <= object1_X2Pos && object2_Y2Pos >= object1_Y1Pos && object2_Y2Pos <= object1_Y2Pos) ||
    (object2_X2Pos >= object1_X1Pos && object2_X2Pos <= object1_X2Pos && object2_Y1Pos >= object1_Y1Pos && object2_Y1Pos <= object1_Y2Pos) ||
    (object2_X2Pos >= object1_X1Pos && object2_X2Pos <= object1_X2Pos && object2_Y2Pos >= object1_Y1Pos && object2_Y2Pos <= object1_Y2Pos))
    {return true;}

    else
        return false;*/

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
