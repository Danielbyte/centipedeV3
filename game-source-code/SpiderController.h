#ifndef SPIDERCONTROLLER_H
#define SPIDERCONTROLLER_H
#include "Spider.h"
#include "SfmlDataType.h"
#include "GameDataType.h"
#include <ctime>


class SpiderController
{
public:
    SpiderController(){};
    void update_spider(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Spider>>&);
private:

};
#endif // SPIDERCONTROLLER_H
