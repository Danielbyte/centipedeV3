#include "Spider.h"

Spider::Spider():
    xFastMovementSpeed{2},
    xSlowMovementSpeed{1},
    yMovementSpeed{2},
    counter{0},
    spiderSpawnRate{15}, // spawn after every 15 secs
    canSpawnSpider{false},
    isNew{true}
    {}

void Spider::set_starting_direction(Direction dir)
{
    start_direction = dir;
}

Direction Spider::get_starting_direction() const
{
    return start_direction;
}

void Spider::setXFastMovementSpeed()
{
    xFastMovementSpeed = xFastMovementSpeed * -1;
}

void Spider::setXSlowMoventSpeed()
{
    xSlowMovementSpeed = xSlowMovementSpeed * -1;
}

int Spider::getXFastMovementSpeed() const
{
    return xFastMovementSpeed;
}

int Spider::getXSlowMovementSpeed() const
{
    return xSlowMovementSpeed;
}

int Spider::getYMovementSpeed() const
{
    return yMovementSpeed;
}

int Spider::getSpideSpawnRate() const
{
    return spiderSpawnRate;
}

void Spider::setIfCanSpawnSpider(bool var)
{
    canSpawnSpider = var;
}

bool Spider::getIfCanSpawnSpider() const
{
    return canSpawnSpider;
}

vector2f Spider::get_position() const
{
    return pos;
}

void Spider::decrement_counter()
{
    if(counter > 0)
    {
        counter--;
    }
}

int Spider::get_counter() const
{
    return counter;
}

void Spider::set_counter(int var)
{
    counter = var;
}

void Spider::set_position(vector2f pos_)
{
    pos = pos_;
}

bool Spider::getIsNew() const
{
    return isNew;
}

void Spider::setToOld(bool var)
{
    isNew = var;
}
