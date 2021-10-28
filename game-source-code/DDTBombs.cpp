#include "DDTBombs.h"

DDTBombs::DDTBombs(vector2f pos_):
    pos{pos_}
    {
        //a bomb is being created
        ++number_of_bombs;
    }

//zero bombs initially
int DDTBombs::number_of_bombs = 0;

vector2f DDTBombs::get_position() const
{
    return pos;
}

DDTBombs::~DDTBombs()
{
    //update for every bomb object killed
    --number_of_bombs;
}

int DDTBombs::getNumberOfBombs() const
{
    return number_of_bombs;
}
