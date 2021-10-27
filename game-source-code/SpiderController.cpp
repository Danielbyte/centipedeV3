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
        initialize_movement(*spiderObj_iter);
    }

    while(spiderObj_iter != spider_obj.end())
    {
        //if there are no more movement instructions, generate new
        if (movement_logic.empty())
        {
            selection = rand() % 4;
            if (selection == 0)
            {
                move_up();
            }

            else if (selection == 1)
            {
                move_down();
            }

            else if (selection ==2)
            {
                move_diagonal_up();
            }

            else if (selection == 3)
            {
                move_diagonal_down();
            }
        }

        //if there are still instructions to be given, execute those
        if (!movement_logic.empty())
        {
            //get the first instruction
            logic_position = movement_logic.front();
            //if spider is above upper bound limit, then control it back
            auto pos_ = (*spiderObj_iter) -> get_position();
            if(pos_.y + logic_position.y > max_pos)
            {

            }

        }
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
        logic_position.x = spider_speed*direction_marker;
        logic_position.y = -spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_diagonal_down()
{
    auto queue_size = (rand() % max_instruction) + min_instruction;
    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = spider_speed*direction_marker;
        logic_position.y = spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::initialize_movement(shared_ptr<Spider>& spider_object)
{
    int dir = rand() % 2;
    if (dir == 0)
    {
        //moving left
        direction = Direction::Left;
        direction_marker = -1;
        vector2f pos_;
        //place spider on the right (will move from right to left)
        pos_.x = right_pos;
        pos_.y = spawn_height;
        spider_object -> set_position(pos_);
    }

    if (dir == 1)
    {
        //moving right
        direction = Direction::Right;
        direction_marker = 1;
        vector2f pos_;
        //place spider on the left (will move from left to right)
        pos_.x = left_pos;
        pos_.y = spawn_height;
        spider_object -> set_position(pos_);

    }

    //initially move spider diagonally downwards
    move_diagonal_down();
}

void SpiderController::delete_queue()
{
    while(!movement_logic.empty())
    {
        movement_logic.pop();
    }
}
