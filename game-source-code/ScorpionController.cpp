#include "ScorpionController.h"

void ScorpionController::update_scorpion(vector<shared_ptr<Scorpion>>& scorpionObj, vector<shared_ptr<Sprite>>&scorpion_sprite,
        vector<shared_ptr<MushroomField>>& mushField)
{
    animate_scorpion(scorpionObj, scorpion_sprite);
    //only updating when scorpion has been created
    if(!scorpionObj.empty())
    {
        auto scorpionObj_iter = scorpionObj.begin();
        vector2f pos_ = (*scorpionObj_iter) -> getScorpion_position();
        poison_mushroom(pos_, mushField);
    }

}

void ScorpionController::animate_scorpion(vector<shared_ptr<Scorpion>>& scorpionObj, vector<shared_ptr<Sprite>>& scorpion_sprite)
{
    auto scorpion_sprite_iter = scorpion_sprite.begin();
    auto scorpionObj_iter = scorpionObj.begin();
    auto counter = (*scorpionObj_iter) -> get_counter();
    if (counter == 0)
    {
        if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
        (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
    }

    if (counter == 5)
    {
        if(!scorpion_texture.loadFromFile("resources/scorpion2.png")) throw CouldNotLoadPicture{};
        (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
    }

    if(counter == 10)
    {
        if(!scorpion_texture.loadFromFile("resources/scorpion3.png")) throw CouldNotLoadPicture{};
        (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
    }

    if(counter == 15)
    {
        if(!scorpion_texture.loadFromFile("resources/scorpion4.png")) throw CouldNotLoadPicture{};
        (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
        (*scorpionObj_iter)-> reset_counter();
    }

    pos = (*scorpionObj_iter) -> getScorpion_position();
    pos.x -= (*scorpionObj_iter) -> get_scorpion_speed();

    if (pos.x <= -(offset + Tile_offset))
    {
        scorpion_sprite.erase(scorpion_sprite_iter);
        scorpionObj.erase(scorpionObj_iter);
        return;
    }

    (*scorpionObj_iter)-> set_position(pos);
    (*scorpion_sprite_iter) -> setPosition(pos);
    (*scorpionObj_iter)-> increment_counter();
}

void ScorpionController::poison_mushroom(vector2f pos_, vector<shared_ptr<MushroomField>>& mushField)
{
    for (auto& mushroom : mushField)
    {
        vector2f mushPosition;
        mushPosition.x = mushroom->get_Xpos();
        mushPosition.y = mushroom->get_Ypos();
        auto isCollided = collision.collision_detect(mushPosition, mushWidth, mushHeight, pos_, scorpion_width,
            scorpion_height);

        if (isCollided)
        {
            mushroom->changeToPoison();
        }
    }

}

vector2f ScorpionController::position_to_spawn_scorpion()
{
    vector2f spawn_pos;
    spawn_pos.x = (30.f)*offset;
    //randomly generate y position keeping in mind that no spawn in player area
    srand((unsigned int)time(0));
    int min = 3;
    int max = 20;

    spawn_pos.y = (float)(((rand() % max) + min)*offset);
    return spawn_pos;
}
