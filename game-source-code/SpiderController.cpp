#include "SpiderController.h"

SpiderController::SpiderController(){};

void SpiderController::update_spider(vector<shared_ptr<Sprite>>& spider_sprite, vector<shared_ptr<Spider>>& spider_obj)
{

    auto spiderObj_iter = spider_obj.begin();
    auto spiderSprite_iter = spider_sprite.begin();

    while(spiderObj_iter != spider_obj.end())
    {
        ++spiderObj_iter;
        ++spiderSprite_iter;
    }
}
