#include "MushroomFieldController.h"

MushroomFieldController::MushroomFieldController():
    percentage_chance{15}
    {
        create_mushrooms();
    }

void MushroomFieldController::create_mushrooms()
{
    srand(time(0));
    //mushArray = 0;
    //mushArray = new int*[30];
    //for(int i =0; i < 33; i++){mushArray[i] = new int[32]{0};}
    for (auto row = 0; row < 32-2; row++)
    {
        for (auto col =0; col < 30; col++)
        {
            //generate a random number between 1 and 100
            auto frequency = (rand() % 100) + 1;

            if (frequency <= percentage_chance)
            {
                //Do nor spawn mushroom at this row for proper creation of cent
               if(row != 1)
                {
                    mushArray[row][col] = new MushroomField(row, col);
                }
                //mushrooms_.push_back(mushroom_ptr);
            }
            else
                mushArray[row][col] = NULL;
        }
    }

}

bool MushroomFieldController::isMushroom(int x, int y)
{
    if (mushArray[x][y] != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MushroomFieldController::SpawnMushroomAt_position(int row, int col)
{
    if(isMushroom(row, col) == false)
    {
        mushArray[row][col] = new MushroomField(row, col);
    }
}
