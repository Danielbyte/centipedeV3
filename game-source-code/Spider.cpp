#include "Spider.h"

Spider::Spider():
    xFastMovementSpeed{2},
    xSlowMovementSpeed{1},
    yMovementSpeed{2},
    counter{0},
    spiderSpawnRate{15}, // spawn after every 15 secs
    canSpawnSpider{false},
    isNew{true},
    lunch_time{5} //lunch time is 5 sec
    {
        pos.x = -32.0f;
        pos.y = 0.0f;
    }

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

sf::Vector2f Spider::get_position() const
{
    return pos;
}

void Spider::increment_counter()
{
        counter++;
}

int Spider::get_counter() const
{
    return counter;
}

void Spider::reset_counter()
{
    counter = 0;
}

void Spider::set_position(sf::Vector2f pos_)
{
    pos = pos_;
}

bool Spider::getIsNew() const
{
    return isNew;
}

void Spider::setToOld()
{
    isNew = false;
}

bool Spider::getIsHungry()
{
    int decision = (int)(rand() % 2);

    if (decision == 0)
    {
        isHungry = false;
    }
    else if (decision == 1)
    {
        isHungry = true;
    }

    return isHungry;
}

float Spider::getSpider_lunch_time() const
{
    return lunch_time;
}

void Spider::play_sound()
{
    if (pos.x >= -15.0f && pos.x <= 495.0f)
        sound_manager->playSpiderSound();
}
