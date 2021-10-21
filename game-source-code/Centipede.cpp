#include "Centipede.h"

Centipede::Centipede():
    centipede_speed{2},
    head{false},
    x_initial{14},
    y_initial{1},
    isMovingUp{false},
    isMovingDown{false},
    moveDown{false},
    moveUp{false},
    update_counter{1},
    isActive{true}, //centipede segment initially alive
    counter{0}
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

void Centipede::setIsMovingDown(bool var)
{
  isMovingDown = var;
}

void Centipede::setIsMovingUp(bool var)
{
  isMovingUp = var;
}

void Centipede::setMoveDown(bool var)
{
    moveDown = var;
}

void Centipede::setMoveUp(bool var)
{
    moveUp = var;
}

bool Centipede::getIsMovingDown() const
{
    return isMovingDown;
}

bool Centipede::getIsMovingUp() const
{
    return isMovingUp;
}

bool Centipede::getMoveDown() const
{
    return moveDown;
}

bool Centipede::getMoveUp() const
{
    return moveUp;
}

void Centipede::setCentipedeSpeed (int speed)
{
    centipede_speed = speed;
}

void Centipede::setUpdate_counter(int var)
{
    update_counter -= var;
}

int Centipede::getUpdate_counter() const
{
    return update_counter;
}

void Centipede::resetUpdate_counter()
{
    update_counter = 1;
}

void Centipede::setSegment_status(bool var)
{
    isActive = var;
}

bool Centipede::getSegment_status() const
{
    return isActive;
}

void Centipede::set_counter(int var)
{
    counter += var;
}

int Centipede::get_counter() const
{
    return counter;
}

void Centipede::reset_counter()
{
    counter = 0;
}
