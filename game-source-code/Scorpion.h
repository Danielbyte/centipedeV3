#ifndef SCORPION_H
#define SCORPION_H
#include "SfmlDataType.h"
#include "StopWatch.h"
#include "GameDataType.h"

class Scorpion
{
public:
    Scorpion();
    //update the scorpion sprite
    update(shared_ptr<Sprite>&);
    move_scorpion();
private:
    vector2f pos;
    float scorpion_speed;

    //time to set movement of scorpion
    StopWatch time;

};

#endif // SCORPION_H
