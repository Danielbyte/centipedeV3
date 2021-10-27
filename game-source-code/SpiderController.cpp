#include "SpiderController.h"

SpiderController::SpiderController():
    spider_speed{2},
    left_pos{-8},
    right_pos{488},
    spawn_height{312},
    max_pos{312},
    min_pos{488},
    min_instruction{9},
    max_instruction{32}

{}

void SpiderController::update_spider(vector<shared_ptr<Sprite>>& spider_sprite, vector<shared_ptr<Spider>>& spider_obj)
{

    //It is known that there will be only one spider at a time
    auto spiderObj_iter = spider_obj.begin();
    auto spiderSprite_iter = spider_sprite.begin();
    auto isNew = (*spiderObj_iter) -> getIsNew();

    if(isNew)
    {
        //should initialize the spider
        initialize_movement();
    }

    while(spiderObj_iter != spider_obj.end())
    {
        ++spiderObj_iter;
        ++spiderSprite_iter;
    }
}

void SpiderController::move_up()
{
    auto queue_size = (rand() % max_instruction) + min_instruction;

    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = 0;
        logic_position.y = -spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_down()
{
    auto queue_size = (rand() % max_instruction) + min_instruction;

    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = 0;
        logic_position.y = spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_diagonal_up()
{
    auto queue_size = (rand() % max_instruction) + min_instruction;
    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = spider_speed*direction;
        logic_position.y = -spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_diagonal_down()
{
    auto queue_size = (rand() % max_instruction) + min_instruction;
    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = spider_speed*direction;
        logic_position.y = spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::initialize_movement()
{

}
