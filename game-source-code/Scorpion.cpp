#include "Scorpion.h"
#include "Logic.h"

Scorpion::Scorpion():
    scorpion_speed{2},
    spawnScorpion_rate{5}, //spawn scorpion after 10 seconds
    canCreate_scorpion{false},
    counter{0},
    control{0}
{
    pos.x = (30.f)*offset;
    pos.y = 160.f;
}

/*vector2f Scorpion::create_scorpion()
{
    //set the position of scorpion
    pos.x = (30.f)*offset; // scorpion will move from right to left

    srand(time(0));
    // randomly generate row position bearing in mind that it should not
    // be in player area.
    if (control == 1)
    {
        pos.y = 160.f;
    }
    if (control == 2)
    {
        pos.y = 176.f;

    }

    if (control == 3)
    {
        pos.y = 208.f;
        control = 0;
    }
}*/

bool Scorpion::getIfCanSpawn_scorpion() const
{
    return canCreate_scorpion;
}

void Scorpion::setIfCanSpawn_scorpion(bool var)
{
    canCreate_scorpion = var;
}

void Scorpion::reset_counter()
{
    counter = 0;
}

void Scorpion::increment_counter()
{
    counter++;
}

int Scorpion::get_counter() const
{
    return counter;
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

float Scorpion::get_scorpion_speed() const
{
    return scorpion_speed;
}

void Scorpion::set_position(vector2f pos)
{
    this -> pos = pos;
}
