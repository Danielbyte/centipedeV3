#include "Scorpion.h"
#include "Logic.h"

Scorpion::Scorpion():
    scorpion_speed{2},
    spawnScorpion_rate{8}, //spawn scorpion after 5 seconds
    canCreate_scorpion{false},
    counter{0},
    control{0}
{
}

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

float Scorpion::getScorpion_spawnRate() const
{
    return spawnScorpion_rate;
}

sf::Vector2f Scorpion::getScorpion_position() const
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

void Scorpion::set_position(sf::Vector2f pos)
{
    this -> pos = pos;
}
