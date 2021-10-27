#ifndef SPIDER_H
#define SPIDER_H

#include "GameDataType.h"
#include "SfmlDataType.h"

class Spider
{
public:
    //The plan is to get spider moving from left to right in random chances
    Spider();
    void set_starting_direction(Direction);
    Direction get_starting_direction() const;

    void setXFastMovementSpeed();
    void setXSlowMoventSpeed();
    int getXFastMovementSpeed() const;
    int getXSlowMovementSpeed() const;
    int getYMovementSpeed() const;

    int getSpideSpawnRate() const;

    //set if can spider can be spawned
    void setIfCanSpawnSpider(bool);
    bool getIfCanSpawnSpider() const;

    vector2f get_position() const;

    void decrement_counter();
    void set_counter(int);
    int get_counter() const;

    void set_position(vector2f);
    bool getIsNew() const;
    void setToOld();

private:
    int xFastMovementSpeed;
    int xSlowMovementSpeed;
    int yMovementSpeed;
    int counter;
    vector2f pos;
    int spiderSpawnRate;
    Direction start_direction;
    bool canSpawnSpider;

    //variable to let centipede controller if it is a new spider
    bool isNew;

};
#endif // SPIDER_H
