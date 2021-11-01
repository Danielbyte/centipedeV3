#include "FleaController.h"

FleaController::FleaController():
     min_mushrooms{5} //if there is less than 5 mushes in player area, call abuti flea
     {}

void FleaController::update_flea(vector<shared_ptr<Flea>>& flea_object, vector<shared_ptr<Sprite>>& flea_sprite,
                                 shared_ptr<MushroomFieldController>& mushField)
{
    //only going to have one flea per instance
    auto flea_sprite_iter = flea_sprite.begin();
    auto flea_object_iter = flea_object.begin();
    auto pos_ = (*flea_sprite_iter) -> getPosition();
    auto flea_speed = (*flea_object_iter) ->get_flea_speed();
    pos_.y += flea_speed;

    if(pos_.y >= windowHeight)
    {
        flea_object.clear();
        flea_sprite.clear();
        std::cout << "destroyed flea"<< std::endl;
        return;
    }
    else
    {
        (*flea_sprite_iter) -> setPosition(pos_);
        (*flea_object_iter) -> set_position(pos_);
    }

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
