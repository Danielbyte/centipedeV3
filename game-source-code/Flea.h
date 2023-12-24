#ifndef FLEA_H
#define FLEA_H

#include "GameDataType.h"
#include "gameResources.h"
#include "soundManager.h"

class Flea
{
public:
    Flea();
    sf::Vector2f get_position() const;
    int get_flea_speed() const;
    void double_flea_speed();
    void set_position(sf::Vector2f);
    int get_flea_spawn_chance() const;
    void decrement_health();
    int get_flea_health() const;

    int get_spawn_rate() const;
    void reset_spawn_rate();
    void increment_spawn_rate();

    void increment_counter();
    int get_counter() const;
    void reset_counter();

private:
    int flea_speed;
    sf::Vector2f pos;
    //health of flea
    int health;
    //the rate at which the flea will spawn a mushroom(i.e once in every 8 frames)
    int spawn_rate;
    //variable for animation
    int counter;

    shared_ptr<SoundManager>sound_manager = std::make_shared<SoundManager>();

};
#endif // FLEA_H
