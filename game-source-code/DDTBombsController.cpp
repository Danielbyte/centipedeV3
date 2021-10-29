#include "DDTBombsController.h"

DDTBombsController::DDTBombsController():
    canCreateBomb{false}
{}

void DDTBombsController::setIfCanCreateBomb()
{
    srand(time(NULL));
    //generate a random number between 1 and 100
    auto decider1 = (rand() % 100) + 1;

    //generate another random number between 1 and 50;
    auto decider2 = (rand() % 50) + 1;


    //generate a bomb if the above two deciders are equal
    //max bombs = 4
    if((decider1 < decider2))
    {
        canCreateBomb = true;
    }
    else
    {
        canCreateBomb = false;
    }
}

bool DDTBombsController::getIfCanCreateBomb() const
{
    return canCreateBomb;
}

void DDTBombsController::generate_position(shared_ptr<MushroomFieldController>& mushField)
{
    auto row = (rand() % 20) + 6;
    auto col =(rand() % 20) + 6;

    //do not generate on position where there is a mushroom
    while (mushField ->isMushroom(row, col))
    {
        auto row = (rand() % 20) + 6;
        auto col =(rand() % 20) + 6;
    }

    pos.x = col*offset;
    pos.y = row*offset;
}

vector2f DDTBombsController::getGeneratedPosition() const
{
    return pos;
}
