#ifndef LASERSHOTS_H
#define LASERSHOTS
#include "Player.h"

class LaserShots
{
public:
    LaserShots(float dir_x, float dir_y, float laser_speed);
    sf::FloatRect getBounds() const;
    float getLaser_speed() const;
    void update();
    sf::Vector2f getBullet_direction() const;


private:
    int laser_direction;
    sf::Sprite shape;
    sf::Texture* texture;
    sf::Vector2f direction;
    float laserSpeed;

};
#endif // LASERSHOTS_H
