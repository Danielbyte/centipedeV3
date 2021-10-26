#include "SpiderController.h"

void SpiderController::update_spider(vector<shared_ptr<Sprite>>& spider_sprite, vector<shared_ptr<Spider>>& spider_obj)
{
    srand(time(NULL));
    auto random = (rand() % 2) + 1;
    Direction dir;
    if(random == 1)
    {
        dir = Direction::Left;
    }
    else
    {
        dir = Direction::Right;
    }


    auto spiderObj_iter = spider_obj.begin();
    auto spiderSprite_iter = spider_sprite.begin();

    while(spiderObj_iter != spider_obj.end())
    {
       (*spiderObj_iter) -> set_starting_direction(dir);
       auto startDirection = (*spiderObj_iter) -> get_starting_direction();

       if(startDirection == Direction::Left)
       {
           (*spiderObj_iter) -> setXFastMovementSpeed();
           (*spiderObj_iter) -> setXSlowMoventSpeed();
       }

       ++spiderObj_iter;
       ++spiderSprite_iter;
    }
}
