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
    counter2{0}
    {
        //set the initial position of centipede
        pos = vector2f((float)((x_initial*offset) + offset/2), (float)((y_initial*offset)+offset/2));
    }

vector2f Centipede::get_position() const
{
    return pos;
}

void Centipede::move_down()
{
    pos.y -= offset;
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
    pos.y += offset;
}

void Centipede::set_position(vector2f position)
{
    pos = position;
}

void Centipede::set_Xpos(vector2f position_)
{
    pos.x = position_.x;
}

void Centipede::set_Ypos(vector2f _position)
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
