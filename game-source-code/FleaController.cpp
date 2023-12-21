#include "FleaController.h"

FleaController::FleaController():
    min_mushrooms{5} //if there is less than 5 mushes in player area, call abuti flea
{}

void FleaController::update_flea(vector<shared_ptr<Flea>>& flea_object, vector<shared_ptr<sf::Sprite>>& flea_sprite,
                                 vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<MushroomResources>>& mushroom_sprites)
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
        return;
    }
    else
    {
        (*flea_sprite_iter) -> setPosition(pos_);
        (*flea_object_iter) -> set_position(pos_);
        spawn_mushroom(pos_, mushField, mushroom_sprites);
        animate_flea((*flea_object_iter),(*flea_sprite_iter));
    }

}

void FleaController::spawn_mushroom(sf::Vector2f position, vector<shared_ptr<MushroomField>>& mushField, 
    vector<shared_ptr<MushroomResources>>& mushroom_sprites)
{
    //see if there is no mushroom at that position so that the flea can decide to spawn mushroom
    bool isMushroom = false;
    sf::Vector2f mushPosition;
    for (auto& mushroom : mushField)
    {
        
        mushPosition.y = mushroom->get_Ypos();
        mushPosition.x = mushroom->get_Xpos();
        if (mushPosition == position)
        {
            isMushroom = true;
            break;
        }
    }
    if (isMushroom)
    {
        return;
    }
    
    auto random = (rand() % 100 + 1);
    //The position of the flea
    int x = (int)(position.x / offset);
    int y = (int)(position.y / offset);
    if (random <= flea_spawn_chance)
    {
        shared_ptr<MushroomField>newMushroom = std::make_shared<MushroomField>(MushroomField(x, y));

        auto xPos = newMushroom->get_Xpos();
        auto yPos = newMushroom->get_Ypos();
        shared_ptr<MushroomResources>mushroom_sprite = std::make_shared<MushroomResources>(MushroomResources(xPos, yPos));
        mushroom_sprite->update_sprite(newMushroom->getIsPoisoned(), newMushroom->getMush_health());

        mushField.push_back(newMushroom);
        mushroom_sprites.push_back(mushroom_sprite);
    }
}

bool FleaController::set_if_can_spawn_flea(vector<shared_ptr<MushroomField>>& mushField)
{
    int mushrooms_in_player_area = 0;
    for (auto& mushroom : mushField)
    {
        auto player_upper_bound = 376;
        if((mushroom->get_Ypos()) > player_upper_bound)
        {
             //count all mushrooms within mushroom field
             ++mushrooms_in_player_area;             
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

sf::Vector2f FleaController::generate_spawn_position()
{
    int max = 29;
    sf::Vector2f position;
    //spawn from the top
    position.y = 0;

    position.x = (float)((rand() % max)*offset);

    return position;
}

void FleaController::animate_flea(shared_ptr<Flea>& flea_obj_ptr, shared_ptr<sf::Sprite>& flea_sprite_ptr)
{
    auto counter = flea_obj_ptr -> get_counter();
    if(counter == 0)
    {
        flea_texture.loadFromFile("resources/flea1.png");
        flea_sprite_ptr -> setTexture(flea_texture);
    }

        if(counter == 5)
    {
        flea_texture.loadFromFile("resources/flea2.png");
        flea_sprite_ptr -> setTexture(flea_texture);
    }

        if(counter == 10)
    {
        flea_texture.loadFromFile("resources/flea3.png");
        flea_sprite_ptr -> setTexture(flea_texture);
    }

        if(counter == 15)
    {
        flea_texture.loadFromFile("resources/flea4.png");
        flea_sprite_ptr -> setTexture(flea_texture);
        flea_obj_ptr -> reset_counter();
    }

    flea_obj_ptr -> increment_counter();
}
