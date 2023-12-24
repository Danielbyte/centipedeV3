#ifndef LASERSHOTS_H
#define LASERSHOTS
#include "Player.h"

class LaserShots
{
public:
    LaserShots(float dir_x, float dir_y, float laser_speed);
    float getLaser_speed() const;
    sf::Vector2f getBullet_direction() const;


private:
    int laser_direction;
    sf::Sprite shape;
    sf::Vector2f direction;
    float laserSpeed;

};
#endif // LASERSHOTS_H
