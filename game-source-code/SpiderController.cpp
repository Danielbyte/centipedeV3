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
        //std::cout << "I'm new!" << std::endl;
        //should initialize the spider
        initialize_movement(*spiderObj_iter);
    }

    while(spiderObj_iter != spider_obj.end())
    {
        //if there are no more movement instructions, generate new
        if (movement_logic.empty())
        {
            selection = (int)(rand() % 4);
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
            if(pos_.y + logic_position.y < max_pos)
            {
                //first empty the previous instructions, they wrong
                delete_queue();
                //let the spider move down
                auto moveDown_option = (int)(rand() % 2);
                if (moveDown_option == 0)
                {
                    //just move straight down
                    move_down();
                    //std::cout << "y pos: " << pos_.y << std::endl;
                }

                else if (moveDown_option == 1)
                {
                    //move down in a diagonal fashion
                    move_diagonal_down();
                }
                //update to latest movement logic
                logic_position = movement_logic.front();
            }

            //else if the spider moves below the lower bound limit, then control it back
            else if (pos_.y + logic_position.y > min_pos)
            {
                //delete these instructions and move spider straight up or diagonally
                delete_queue();
                auto moveUp_option = (int)(rand() % 2);
                if (moveUp_option == 0)
                {
                    //just move straight up
                    move_up();
                }
                if (moveUp_option == 1)
                {
                    // do so diagonally my friend
                    move_diagonal_up();
                }
            }

            //This is where we get to update our spider object accordingly
            pos_.x += logic_position.x;
            pos_.y += logic_position.y;
            (*spiderObj_iter) -> set_position(pos_);
            movement_logic.pop();
        }

        //update the spider sprite
        auto pos_ = (*spiderObj_iter) -> get_position();
        (*spiderSprite_iter) -> setPosition(pos_);

        if(pos_.x < -offset && direction == Direction::Left)
        {
            spider_obj.erase(spiderObj_iter);
            spider_sprite.erase(spiderSprite_iter);
            return;
        }

        if (pos_.x > (windowWidth + offset) && (direction == Direction::Right))
        {
            spider_obj.erase(spiderObj_iter);
            spider_sprite.erase(spiderSprite_iter);
            return;
        }

        ++spiderObj_iter;
        ++spiderSprite_iter;
    }
}

void SpiderController::move_up()
{
    auto queue_size = (int)((rand() % max_instruction) + min_instruction);

    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = 0;
        logic_position.y = -spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_down()
{
    auto queue_size = (int)((rand() % max_instruction) + min_instruction);

    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = 0;
        logic_position.y = spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_diagonal_up()
{
    auto queue_size = (int)((rand() % max_instruction) + min_instruction);
    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = spider_speed*direction_marker;
        logic_position.y = -spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::move_diagonal_down()
{
    auto queue_size = (int)((rand() % max_instruction) + min_instruction);
    for (auto instruction = 0; instruction < queue_size; instruction++)
    {
        logic_position.x = spider_speed*direction_marker;
        logic_position.y = spider_speed;
        movement_logic.push(logic_position);
    }
}

void SpiderController::initialize_movement(shared_ptr<Spider>& spider_object)
{
    int dir = (int)(rand() % 2);
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

    //Spider is no longer new but old
    spider_object -> setToOld();
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
