#ifndef DDTBOMBS_H
#define DDTBOMBS_H

#include "gameResources.h"

class DDTBombs
{
public:
    DDTBombs();

    sf::Vector2f get_position() const;
    void set_position(sf::Vector2f);
    int getNumberOfBombs() const;
    void setExplosion(bool);
    bool getIfcanExplode() const;
    void increment_counter();
    int get_counter() const;
    void reset_counter();
private:
    sf::Vector2f pos;
    bool canExplode;
    //variable to create animations
    int counter;

    //keep track of the number of bombs
    static int number_of_bombs;

};
#endif // DDTBOMBS_H
