#include "Scorpion.h"

Scorpion::Scorpion():
    scorpion_speed{2},
    spawnScorpion_rate{10}, //spawn scorpion after 10 seconds
    canCreate_scorpion{false},
    isOffScreen{false} //scorpion initially on screen when created
{

}

vector2f Scorpion::create_scorpion()
{

    //set the position of scorpion
    pos.x = 28.f; // scorpion will move from right to left

    srand(time(0));
    int min = 2;
    int max = 5;
    // randomly generate row position bearing in mind that it should not
    // be in player area.
    pos.y = (float)((rand() % (max) + min)*offset);
    return pos;
}

bool Scorpion::getIfCanSpawn_scorpion() const
{
    return canCreate_scorpion;
}

void Scorpion::setIfCanSpawn_scorpion(bool var)
{
    canCreate_scorpion = var;
}

void Scorpion::update(float _time)
{
    //only updating when scorpion has been created
    if (_time > spawnScorpion_rate)
    {
        pos.x -= scorpion_speed;
    }

    if (pos.x <= -offset)
    {
        isOffScreen = true;
    }
    else
    {
        isOffScreen = false;
    }
}

int Scorpion::getScorpion_spawnRate() const
{
    return spawnScorpion_rate;
}
