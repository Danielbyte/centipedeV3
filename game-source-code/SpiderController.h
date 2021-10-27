#ifndef SPIDERCONTROLLER_H
#define SPIDERCONTROLLER_H
#include "Spider.h"
#include "SfmlDataType.h"
#include "GameDataType.h"
#include <ctime>


class SpiderController
{
public:
    SpiderController();
    void update_spider(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Spider>>&);
private:
    void move_up();
    void move_down();
    void move_diagonal_up();
    void move_diagonal_down();
    int selection;

};
#endif // SPIDERCONTROLLER_H
