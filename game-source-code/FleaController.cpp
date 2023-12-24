#include "FleaController.h"

FleaController::FleaController():
    min_mushrooms{5}, //if there is less than 5 mushes in player area, call abuti flea
    previousYpos{0}
{
    load_resources();
}

void FleaController::update_flea(vector<shared_ptr<Flea>>& flea_object, vector<shared_ptr<sf::Sprite>>& flea_sprite,
                                 vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
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
    vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    //see if there is no mushroom at that position so that the flea can decide to spawn mushroom
    bool isMushroom = false;
    sf::Vector2f mushPosition;

    //The position of the flea
    int x = (int)(position.x / offset); //Horizontal spawning position
    int y = (int)(position.y / offset); //Vertical spawning position

    for (auto& mushroom : mushField)
    {
        
        int mushroomXpos = (int)((mushroom->get_Xpos())/offset);
        int mushroomYpos = (int)((mushroom->get_Ypos())/offset);
        if (mushroomXpos == x && mushroomYpos == y)
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
    auto deltaYdistance = abs(y - previousYpos); //This variable monitors the flea to not spawn multiple mushrooms in the same position
    if (random <= flea_spawn_chance && deltaYdistance != 0)
    {
       
        shared_ptr<MushroomField>newMushroom = std::make_shared<MushroomField>(MushroomField(x, y));

        auto xPos = newMushroom->get_Xpos();
        auto yPos = newMushroom->get_Ypos();
        shared_ptr<sf::Sprite>mushroom_sprite = std::make_shared<sf::Sprite>();
        mushroom_sprite->setOrigin(0.0f, 0.0f);
        mushroom_sprite->setPosition(xPos, yPos);
        mushroom_resource->update_sprite(newMushroom->getIsPoisoned(), newMushroom->getMush_health(), mushroom_sprite);
        
        mushField.push_back(newMushroom);
        mushroom_sprites.push_back(mushroom_sprite);
        previousYpos = y;
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
    switch (counter)
    {
    case 0:
        flea_sprite_ptr->setTexture(flea1_t);
        break;
    case 5:
        flea_sprite_ptr->setTexture(flea2_t);
        break;
    case 10:
        flea_sprite_ptr->setTexture(flea3_t);
        break;
    case 15:
        flea_sprite_ptr->setTexture(flea4_t);
        flea_obj_ptr->reset_counter();
        break;
    default:
        break;
    }
    flea_obj_ptr -> increment_counter();
}

void FleaController::load_resources()
{
    flea1_t.loadFromFile("resources/flea1.png");
    flea2_t.loadFromFile("resources/flea2.png");
    flea3_t.loadFromFile("resources/flea3.png");
    flea4_t.loadFromFile("resources/flea4.png");
}
