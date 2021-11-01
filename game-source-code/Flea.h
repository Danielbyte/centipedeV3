#ifndef FLEA_H
#define FLEA_H

#include "GameDataType.h"
#include "SfmlDataType.h"

class Flea
{
public:
    Flea();
    vector2f get_position() const;
    int get_flea_speed() const;
    void set_position(vector2f);
    int get_flea_spawn_chance() const;
    void decrement_health();
    int get_flea_health() const;

    int get_spawn_rate() const;
    void reset_spawn_rate();
    void increment_spawn_rate();

    void increment_counter();
    int get_counter() const;
    void decrement_counter();

private:
    int flea_speed;
    vector2f pos;
    //health of flea
    int health;
    //the rate at which the flea will spawn a mushroom(i.e once in every 8 frames)
    int spawn_rate;
    //variable for animation
    int counter;

};
#endif // FLEA_H
