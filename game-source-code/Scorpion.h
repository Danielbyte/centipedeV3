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
    //update the scorpion sprite
    void update(shared_ptr<Sprite>&, float);
    vector2f create_scorpion(const vector<shared_ptr<Centipede>>&);
    void get_scorpionPos();
    void setIfCanSpawn_scorpion(bool var);
    bool getIfCanSpawn_scorpion() const;
    int getScorpion_spawnRate() const;
    vector2f getScorpion_position() const;

    bool getIfOffScreen() const;

    Texture scorpion_texture;

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
