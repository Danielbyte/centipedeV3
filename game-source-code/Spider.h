#ifndef SPIDER_H
#define SPIDER_H

#include "GameDataType.h"
#include "SfmlDataType.h"

class Spider
{
public:
    //The plan is to get spider moving from left to right in random chances
    void set_starting_direction(Direction);
    Direction get_starting_direction() const;

    void setXFastMovementSpeed();
    void setXSlowMoventSpeed();
    int getXFastMovementSpeed() const;
    int getXSlowMovementSpeed() const;

private:
    int xFastMovementSpeed;
    int xSlowMovementSpeed;
    int yMovementSpeed;
    int counter;
    vector2f pos;

};
#endif // SPIDER_H
