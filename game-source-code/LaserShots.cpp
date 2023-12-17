#include "LaserShots.h"

LaserShots::LaserShots(float dir_x, float dir_y, float laser_speed)
{
    //this ->shape.setTexture(*texture);
    this ->direction.x = dir_x;
    this ->direction.y = dir_y;
    this ->laserSpeed = laser_speed;
    //this ->shape.setPosition(pos_x, pos_y);
}

void LaserShots::update()
{
    //this ->shape.move(this ->laserSpeed*this ->direction);
}

sf::Vector2f LaserShots::getBullet_direction() const
{
    return direction;
}

float LaserShots::getLaser_speed() const
{
    return laserSpeed;
}
