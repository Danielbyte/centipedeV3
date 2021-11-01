#include "FleaController.h"

FleaController::FleaController():
     min_mushrooms{5} //if there is less than 5 mushes in player area, call abuti flea
     {}

void FleaController::update_flea(vector<shared_ptr<Flea>>& flea_object, vector<shared_ptr<Sprite>>& flea_sprite,
                                 shared_ptr<MushroomFieldController>& mushField)
{

}

void FleaController::spawn_mushroom(vector2f position, shared_ptr<MushroomFieldController>& mushField)
{
    //The position of the flea
    int x = (int)(position.x/offset);
    int y = (int)(position.y/offset);

    //see if there is no mushroom at that position so that the flea can decide to spawn mushroom
    if(mushField -> mushArray[y][x] == NULL)
    {
        auto random = (rand() % 100 + 1);
        if (random <= flea_spawn_chance)
        {
            mushField -> mushArray[y][x] = new MushroomField(y,x);
            return;
        }
    }
}

bool FleaController::set_if_can_spawn_flea(shared_ptr<MushroomFieldController>& mushField)
{
    int mushrooms_in_player_area = 0;
    for (auto row = 0; row < 32; row++)
    {
        for(auto col = 0; col < 30; col++)
        {
            auto player_upper_bound = 376;
            if(row*offset > player_upper_bound)
            {
                //count all mushrooms within mushroom field
                if(mushField -> mushArray[row][col] != NULL)
                {
                    ++mushrooms_in_player_area;
                }
            }
        }
    }

    if (mushrooms_in_player_area < min_mushrooms)
    {
        return true;
    }
    else
    {
        return false;
    }

}

vector2f FleaController::generate_spawn_position()
{
    int max = 29;
    vector2f position;
    //spawn from the top
    position.y = 0;

    position.x = (rand() % max)*offset;

    return position;
}
