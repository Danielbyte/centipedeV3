#include "Centipede.h"

Centipede::Centipede():
    centipede_speed{2},
    head{false},
    x_initial{14},
    y_initial{1},
    up{false},
    down{false},
    left{true},
    right{false},
    wasMovingLeft{true},
    wasMovingRight{false},
    wasMovingUp{false},
    wasMovingDown{true},
    isActive{true}, //centipede segment initially alive
    counter{0},
    counter2{0},
    isCentipedePoisoned{false},
    animation_loop{0},
    isHit{false}, //centipede initially not hit by bomb
    rotation{0.0f},
    inDeathAnimation{false},
    canDestroy{false}
    {
        //set the initial position of centipede
        pos = sf::Vector2f((float)((x_initial*offset) + offset/2), (float)((y_initial*offset)+offset/2));
    }

sf::Vector2f Centipede::get_position() const
{
    return pos;
}

void Centipede::move_down()
{
    pos.y += centipede_speed;
}

void Centipede::move_left()
{
    pos.x -= centipede_speed;
}

void Centipede::move_right()
{
    pos.x += centipede_speed;
    if(pos.x>480)
    {
       pos.x = 480;
    }
}

void Centipede::move_up()
{
    pos.y -= centipede_speed;
}

void Centipede::set_position(sf::Vector2f position)
{
    pos = position;
}

void Centipede::set_Xpos(sf::Vector2f position_)
{
    pos.x = position_.x;
}

void Centipede::set_Ypos(sf::Vector2f _position)
{
    pos.y = _position.y;
}

int Centipede::getCentipede_speed() const
{
    return centipede_speed;
}

void Centipede::setHead(bool head_)
{
    head = head_;
}

bool Centipede::getHead() const
{
    return head;
}

void Centipede::setCentipedeSpeed (int speed)
{
    centipede_speed = speed;
}

void Centipede::setSegment_status(bool var)
{
    isActive = var;
}

bool Centipede::getSegment_status() const
{
    return isActive;
}

void Centipede::increment_counter()
{
    counter ++;
}

int Centipede::get_counter() const
{
    return counter;
}

void Centipede::reset_counter()
{
    counter = 0;
}

void Centipede::incrementCounter2()
{
    counter2++;
}

int Centipede::getCounter2() const
{
    return counter2;
}

bool Centipede::getDown() const
{
    return down;
}

bool Centipede::getUp() const
{
    return up;
}

void Centipede::resetCounter2()
{
    counter2 = 0;
}

bool Centipede::getRight() const
{
    return right;
}

bool Centipede::getWasMovingDown() const
{
    return wasMovingDown;
}

bool Centipede::getWasMovingUp() const
{
    return wasMovingUp;
}

bool Centipede::getWasMovingLeft() const
{
    return wasMovingLeft;
}

bool Centipede::getWasMovingRight() const
{
    return wasMovingRight;
}

void Centipede::setUp(bool var)
{
    up = var;
}

void Centipede::setDown(bool var)
{
    down = var;
}

void Centipede::setLeft(bool var)
{
    left = var;
}

void Centipede::setRight(bool var)
{
    right = var;
}

void Centipede::setWasMovingDown(bool var)
{
    wasMovingDown = var;
}

void Centipede::setWasMovingLeft(bool var)
{
    wasMovingLeft = var;
}

void Centipede::setWasMovingRight(bool var)
{
    wasMovingRight = var;
}

void Centipede::setWasMovingUp(bool var)
{
    wasMovingUp = var;
}

bool Centipede::getLeft() const
{
    return left;
}

void Centipede::setToPoisoned()
{
    isCentipedePoisoned = true;
}

bool Centipede::getIsCentipedePoisoned() const
{
    return isCentipedePoisoned;
}

void Centipede::cure_from_poison()
{
    isCentipedePoisoned = false;
}

void Centipede::increment_animation()
{
    animation_loop++;
}
int Centipede::get_anime_loop() const
{
    return animation_loop;
}
void Centipede::reset_animation_loop()
{
    animation_loop = 0;
}

void Centipede::is_hit(bool var)
{
    isHit = var;
}
bool Centipede::get_is_hit() const
{
    return isHit;
}

void Centipede::setRotation(float _rotation)
{
    rotation = _rotation;
}

float Centipede::getRotation() const
{
    return rotation;
}

void Centipede::startDeathAnimation()
{
    inDeathAnimation = true;
    death_animation_watch->restart();
}

void Centipede::destroy_object()
{
    canDestroy = true;
}

bool Centipede::CanDestroy() const
{
    return canDestroy;
}

float Centipede::getAnimationTime() const
{
    return (death_animation_watch->getTimeElapsed());
}

bool Centipede::isInDeathAnimation() const
{
    return inDeathAnimation;
}