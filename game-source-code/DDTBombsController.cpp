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

     //create a temp object to bomb object to see number of
     //bombs already spawned
     vector2f temp;
     temp.x = 0.f;
     temp.y - 0.f;
     auto dummy_bomb = new DDTBombs(temp);
     auto numberOfSpawnedBombs = (dummy_bomb -> getNumberOfBombs()) - 1;
     std::cout << "number of bombs: " <<numberOfSpawnedBombs <<std::endl;
     delete dummy_bomb;

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
