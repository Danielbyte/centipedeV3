#ifndef LASERSHOTS_H
#define LASERSHOTS
#include "Player.h"
#include "SfmlDataType.h"

class LaserShots
{
public:
    LaserShots(float dir_x, float dir_y, float laser_speed);
    FloatRect getBounds() const;
    float getLaser_speed() const;
    void update();
    vector2f getBullet_direction() const;


private:
    int laser_direction;
    Sprite shape;
    Texture* texture;
    vector2f direction;
    float laserSpeed;

};
#endif // LASERSHOTS_H
