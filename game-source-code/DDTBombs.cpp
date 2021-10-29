#include "DDTBombs.h"

DDTBombs::DDTBombs():
    canExplode{false}
{}

//zero bombs initially
int DDTBombs::number_of_bombs = 0;

vector2f DDTBombs::get_position() const
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

void DDTBombs::set_position(vector2f pos_)
{
    pos = pos_;
}
