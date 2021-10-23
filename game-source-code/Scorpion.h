#ifndef SCORPION_H
#define SCORPION_H
#include "SfmlDataType.h"
#include "StopWatch.h"
#include "GameDataType.h"
#include "ctime"

class Scorpion
{
public:
    Scorpion();
    //update the scorpion sprite
    void update(float);
    vector2f create_scorpion();
    void get_scorpionPos();
    void setIfCanSpawn_scorpion(bool var);
    bool getIfCanSpawn_scorpion() const;
    int getScorpion_spawnRate() const;
private:
    vector2f pos;
    float scorpion_speed;
    float spawnScorpion_rate;

    //time to set movement of scorpion
    StopWatch time_;
    bool canCreate_scorpion;

    //notify if scorpion goes out of screen to free resources
    bool isOffScreen;

};

#endif // SCORPION_H
