#ifndef SCORPION_H
#define SCORPION_H

#include "StopWatch.h"
#include "GameDataType.h"
#include "Centipede.h"
#include "soundManager.h"
#include "ctime"

class Scorpion
{
public:
    Scorpion();
    void setIfCanSpawn_scorpion(bool var);
    bool getIfCanSpawn_scorpion() const;
    float getScorpion_spawnRate() const;
    sf::Vector2f getScorpion_position() const;

    bool getIfOffScreen() const;
    void reset_counter();
    void increment_counter();
    int get_counter() const;
    float get_scorpion_speed() const;
    void set_position(sf::Vector2f);
    void play_sound();
    void startDeathAnimation();
    bool isInDeathAnimation() const;
    void destroy_object();
    bool CanDestroy() const;
    float getAnimationTime() const;


private:
    sf::Vector2f pos;
    float scorpion_speed;
    float spawnScorpion_rate;

    //time to set movement of scorpion
    StopWatch time_;
    bool canCreate_scorpion;

    //notify if scorpion goes out of screen to free resources
    bool isOffScreen;
    int counter;
    int control;
    shared_ptr<SoundManager>sound_manager = std::make_shared<SoundManager>();

    bool inDeathAnimation;
    bool canDestroy;
    shared_ptr<StopWatch>death_animation_watch = std::make_shared<StopWatch>();
};

#endif // SCORPION_H
