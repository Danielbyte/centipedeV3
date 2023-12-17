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

bool Collision::collision_detect(sf::Vector2f obj1Pos, float obj1Width, float obj1Height, sf::Vector2f obj2Pos, float obj2Width, float obj2Height)
{
    //object 1 box
    auto left_side1 = obj1Pos.x;
    auto right_side1 = left_side1 + obj1Width;
    auto top_side1 = obj1Pos.y;
    auto bottom_side1 = top_side1 + obj1Height;

    //object 2 box
    auto left_side2 = obj2Pos.x;
    auto right_side2 = left_side2 + obj2Width;
    auto top_side2 = obj2Pos.y;
    auto bottom_side2 = top_side2 + obj2Height;

    if(right_side1>left_side2 && left_side1<right_side2 && bottom_side1>top_side2 && top_side1<bottom_side2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
