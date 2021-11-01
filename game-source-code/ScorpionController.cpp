#include "ScorpionController.h"

void ScorpionController::update_scorpion(vector<shared_ptr<Scorpion>>& scorpionObj, vector<shared_ptr<Sprite>>&scorpion_sprite,
        shared_ptr<MushroomFieldController>& mushField)
{
    //only updating when scorpion has been created
    auto scorpion_sprite_iter = scorpion_sprite.begin();
    auto scorpionObj_iter = scorpionObj.begin();

   auto counter = (*scorpionObj_iter) -> get_counter();
    //isOffScreen = false;
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
        std::cout<< "Deleted scorpion!" << std::endl;
        return;
    }

     (*scorpionObj_iter)-> set_position(pos);
    (*scorpion_sprite_iter) -> setPosition(pos);
    (*scorpion_sprite_iter) -> setOrigin(vector2f(0.f,0.f));
    (*scorpionObj_iter)-> increment_counter();
}
