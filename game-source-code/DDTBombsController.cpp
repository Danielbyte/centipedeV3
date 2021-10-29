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
    std::cout<< "start" << std::endl;
    auto row = (rand() % 20) + 6;
    auto col =(rand() % 20) + 6;
   /* if (!mushField ->isMushroom(row, col))
    {
        return;
    }



    //do not generate on position where there is a mushroom
    std::cout << "Came!" << std::endl;
    bool isGenerated = false;
    while (mushField ->isMushroom(row, col))
    {
        std::cout << "Caame!" << std::endl;
        auto row = (rand() % 20) + 6;
        auto col =(rand() % 20) + 6;
    }*/

    pos.x = col*offset;
    pos.y = row*offset;

    std::cout << "ended" << std::endl;
}

vector2f DDTBombsController::getGeneratedPosition() const
{
    return pos;
}
