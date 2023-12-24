#include "Flea.h"

Flea::Flea():
    flea_speed{5},
    health{2}, //eliminated by two player shots
    spawn_rate{0},//starts at 0 and will be controlled by Flea controller
    counter{0}
{
    sound_manager->playFleaSound();
}

int Flea::get_flea_speed() const
{
    return flea_speed;
}

sf::Vector2f Flea::get_position() const
{
    return pos;
}

void Flea::set_position(sf::Vector2f pos)
{
    this -> pos = pos;
}

void Flea::decrement_health()
{
    if(health > 0)
    {
        health--;
    }
}

int Flea::get_flea_health() const
{
    return health;
}

void Flea::increment_spawn_rate()
{
    spawn_rate++;
}

void Flea::reset_spawn_rate()
{
    spawn_rate = 0;
}

int Flea::get_spawn_rate() const
{
    return spawn_rate;
}

void Flea::increment_counter()
{
    counter++;
}

int Flea::get_counter() const
{
   return counter;
}

void Flea::reset_counter()
{
    counter = 0;
}

void Flea::double_flea_speed()
{
    flea_speed = 2*flea_speed;
}

