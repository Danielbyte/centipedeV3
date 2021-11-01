#include "FleaController.h"

FleaController::FleaController() {};

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

}
