#include "Scorpion.h"

Scorpion::Scorpion():
    scorpion_speed{2},
    spawnScorpion_rate{15}, //spawn scorpion after 10 seconds
    canCreate_scorpion{false},
    isOffScreen{false} //scorpion initially on screen when created
{

}

vector2f Scorpion::create_scorpion()
{

    //set the position of scorpion
    pos.x = (29.f)*offset; // scorpion will move from right to left

    srand(time(0));
    int min = 2;
    int max = 6;
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

void Scorpion::update(shared_ptr<Sprite>& scorpion_sprite,float _time)
{
    //only updating when scorpion has been created
    if (_time > spawnScorpion_rate)
    {
        pos.x -= 2;
        scorpion_sprite -> setPosition(pos);
        //std::cout << "Xpos: " << pos.x<<std::endl;
    }

    if (pos.x <= -offset)
    {
        scorpion_sprite.reset(new Sprite);
    }

}

int Scorpion::getScorpion_spawnRate() const
{
    return spawnScorpion_rate;
}

vector2f Scorpion::getScorpion_position() const
{
    return pos;
}

bool Scorpion::getIfOffScreen() const
{
    return isOffScreen;
}


