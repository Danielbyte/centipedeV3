#include "DDTBombs.h"

DDTBombs::DDTBombs():
    canExplode{false},
    counter{0}
{}

//zero bombs initially
int DDTBombs::number_of_bombs = 0;

sf::Vector2f DDTBombs::get_position() const
{
    return pos;
}

void DDTBombs::setExplosion(bool var)
{
    canExplode = var;
}

bool DDTBombs::getIfcanExplode() const
{
    return canExplode;
}
/*DDTBombs::~DDTBombs()
{
    //update for every bomb object killed
    --number_of_bombs;
}*/

int DDTBombs::getNumberOfBombs() const
{
    return number_of_bombs;
}

void DDTBombs::set_position(sf::Vector2f pos_)
{
    pos = pos_;
}

int DDTBombs::get_counter() const
{
    return counter;
}

void DDTBombs::reset_counter()
{
    counter = 0;
}

void DDTBombs::increment_counter()
{
    counter++;
}
