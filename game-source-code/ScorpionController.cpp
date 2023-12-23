#include "ScorpionController.h"

ScorpionController::ScorpionController()
{
    load_resources();
}

void ScorpionController::update_scorpion(vector<shared_ptr<Scorpion>>& scorpionObj, vector<shared_ptr<sf::Sprite>>&scorpion_sprite,
        vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    animate_scorpion(scorpionObj, scorpion_sprite);
    //only updating when scorpion has been created
    if(!scorpionObj.empty())
    {
        auto scorpionObj_iter = scorpionObj.begin();
        sf::Vector2f pos_ = (*scorpionObj_iter) -> getScorpion_position();
        poison_mushroom(pos_, mushField, mushroom_sprites);
    }

}

void ScorpionController::animate_scorpion(vector<shared_ptr<Scorpion>>& scorpionObj, vector<shared_ptr<sf::Sprite>>& scorpion_sprite)
{
    auto scorpion_sprite_iter = scorpion_sprite.begin();
    auto scorpionObj_iter = scorpionObj.begin();
    auto counter = (*scorpionObj_iter) -> get_counter();
    if (counter == 0)
    {
        (*scorpion_sprite_iter) -> setTexture(scorpion1_t);
    }

    if (counter == 5)
    {
        (*scorpion_sprite_iter) -> setTexture(scorpion2_t);
    }

    if(counter == 10)
    {
        (*scorpion_sprite_iter) -> setTexture(scorpion3_t);
    }

    if(counter == 15)
    {
        (*scorpion_sprite_iter) -> setTexture(scorpion4_t);
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

void ScorpionController::poison_mushroom(sf::Vector2f pos_, vector<shared_ptr<MushroomField>>& mushField,
    vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    auto mushroom_sprite = mushroom_sprites.begin();
    for (auto& mushroom : mushField)
    {
        sf::Vector2f mushPosition;
        mushPosition.x = mushroom->get_Xpos();
        mushPosition.y = mushroom->get_Ypos();
        auto isCollided = collision.collision_detect(mushPosition, mushWidth, mushHeight, pos_, scorpion_width,
            scorpion_height);

        if (isCollided)
        {
            mushroom->changeToPoison();
            mushroom_resource->update_sprite(mushroom->getIsPoisoned(), mushroom->getMush_health(), *mushroom_sprite);
        }
        ++mushroom_sprite;
    }

}

sf::Vector2f ScorpionController::position_to_spawn_scorpion()
{
    sf::Vector2f spawn_pos;
    spawn_pos.x = (30.f)*offset;
    //randomly generate y position keeping in mind that no spawn in player area
    srand((unsigned int)time(0));
    int min = 3;
    int max = 20;

    spawn_pos.y = (float)(((rand() % max) + min)*offset);
    return spawn_pos;
}

void ScorpionController::load_resources()
{
    scorpion1_t.loadFromFile("resources/scorpion1.png");
    scorpion2_t.loadFromFile("resources/scorpion2.png");
    scorpion3_t.loadFromFile("resources/scorpion3.png");
    scorpion4_t.loadFromFile("resources/scorpion4.png");
}
