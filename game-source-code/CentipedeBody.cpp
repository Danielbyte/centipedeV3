#include "CentipedeBody.h"

CentipedeBody::CentipedeBody(float xBodyPos, float yBodyPos, CentipedeHead* head_)
{
    counter = 0;
    next_direction = Direction::unknown;
    current_direction = Direction::Left; //centipede initially going left
    head_ptr = head_;
    xBody_pos = xBodyPos;
    yBody_pos = yBodyPos;
    pos = vector2f((float)((xBody_pos*offset)+offset/2), (float)((yBody_pos*offset)+offset/2));
}

float CentipedeBody::get_Xpos() const
{
    return xBody_pos;
}

float CentipedeBody::get_Ypos() const
{
    return yBody_pos;
}

CentipedeHead* CentipedeBody::GetHead() const
{
    return this -> head_ptr;
}

CentipedeBody* CentipedeBody::GetNextBodySegment() const
{
    return this -> next;
}

CentipedeBody* CentipedeBody::GetBodySegmentInfront() const
{
    return this -> ahead_ptr;
}

void CentipedeBody::setHead(CentipedeHead* ptr)
{
    this -> head_ptr = ptr;
}

void CentipedeBody::setBodySegmentInfront(CentipedeBody* ptr)
{
    this -> ahead_ptr = ptr;
}

void CentipedeBody::setNextBodySegment(CentipedeBody* ptr)
{
    this -> next = ptr;
}

void CentipedeBody::update_body()
{
    next_direction = current_direction;
    //check and update if segment behind head
    if (GetBodySegmentInfront() == NULL)
    {
        //need to check the head
        check_head();
    }
    //else there is a body segment in front
    else
    {
        //need to  check the body
        check_body();
    }

    counter = 0;
    //update the next body segment
    if (next != NULL)
    {
        next ->update_body(); //recursion
    }

}

void CentipedeBody::check_head()
{
    if (head_ptr ->get_down())
    {
        current_direction = Direction::Down;
    }

    if (head_ptr ->get_up())
    {
        current_direction = Direction::Up;
    }

    if (head_ptr ->get_left())
    {
        current_direction = Direction::Left;
    }

    if (head_ptr ->get_right())
    {
        current_direction = Direction::Right;
    }
}

void CentipedeBody::check_body()
{
    if (ahead_ptr ->next_direction == Direction::Down)
    {
        current_direction = Direction::Down;
    }

    if (ahead_ptr ->next_direction == Direction::Up)
    {
        current_direction = Direction::Up;
    }

    if (ahead_ptr ->next_direction == Direction::Left)
    {
        current_direction = Direction::Left;
    }

    if (ahead_ptr -> next_direction == Direction::Right)
    {
        current_direction = Direction::Right;
    }
}
