#include "MushroomField.h"

MushroomField::MushroomField(int row, int col):
    mushroom_health{4}, //mushroom health initially = 4
    isPoisoned{false} //mushroom initially not poisoned
    {
        y_position = (float)(col*offset);
        x_position = (float)(row*offset);
    }

float MushroomField::get_Xpos()
{
    return x_position;
}

float MushroomField::get_Ypos()
{
    return y_position;
}

void MushroomField::decrementMush_health()
{
    if (mushroom_health > 0){mushroom_health--;}
    //std::cout << "mush_health: " << mushroom_health << std::endl;
    //if (mushroom_health == 0)
    //{
       // int x = (int)(x_position/offset);
      //  int y = (int)(y_position/offset);
       // ptr -> mushArray[x][y] = 0;
    //}
}

int MushroomField::getMush_health() const
{
    return mushroom_health;
}

void MushroomField::changeToPoison()
{
    isPoisoned = true;
}

bool MushroomField::getIsPoisoned() const
{
    return isPoisoned;
}

