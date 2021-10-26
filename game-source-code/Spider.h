#ifndef SPIDER_H
#define SPIDER_H

#include "GameDataType.h"
#include "SfmlDataType.h"

class Spider
{
public:
    //The plan is to get spider moving from left to right in random chances
    Spider(Direction);
    void set_starting_direction(Direction);
    Direction get_starting_direction() const;

    void setXFastMovementSpeed();
    void setXSlowMoventSpeed();
    int getXFastMovementSpeed() const;
    int getXSlowMovementSpeed() const;
    int getYMovementSpeed() const;

private:
    int xFastMovementSpeed;
    int xSlowMovementSpeed;
    int yMovementSpeed;
    int counter;
    vector2f pos;
    int spiderSpawnRate;
    Direction start_direction;

};
#endif // SPIDER_H
