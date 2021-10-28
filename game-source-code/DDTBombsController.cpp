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
     if(decider1 == decider2)
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
