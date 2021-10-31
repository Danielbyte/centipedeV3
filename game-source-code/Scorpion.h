#ifndef SCORPION_H
#define SCORPION_H

#include "SfmlDataType.h"
#include "StopWatch.h"
#include "GameDataType.h"
#include "Centipede.h"
#include "ctime"

class Scorpion
{
public:
    Scorpion();
    void setIfCanSpawn_scorpion(bool var);
    bool getIfCanSpawn_scorpion() const;
    int getScorpion_spawnRate() const;
    vector2f getScorpion_position() const;

    bool getIfOffScreen() const;
    void reset_counter();
    void increment_counter();
    int get_counter() const;

private:
    vector2f pos;
    float scorpion_speed;
    float spawnScorpion_rate;

    //time to set movement of scorpion
    StopWatch time_;
    bool canCreate_scorpion;

    //notify if scorpion goes out of screen to free resources
    bool isOffScreen;
    int counter;
    int control;

};

#endif // SCORPION_H
