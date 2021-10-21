#include "CentipedeHead.h"

CentipedeHead::CentipedeHead(int bodySegments, bool startOfGame, shared_ptr<MushroomFieldController>& gridPtr):
    x_position{14}, //initial x position
    y_position{1}, //initial y position
    centipede_speed{2}, //set the speed of centipede to two
    up{false},
    down{false},
    left{true}, // The centipede head initially moving left
    right{false},
    isMovingLeft{true},
    isMovingRight{false},
    isMovingUp{false},
    isMovingDown{true} // centipede initially at top of screen and moving down
    {
        mushGridPtr = gridPtr;
        //pointers to behind and in front of body segment
        ahead_ptr = NULL;
        next = NULL; //behind segment

        //pointer to the head
        head_ptr =NULL;

        body_ptr = NULL;

        pos = vector2f((float)((x_position*offset)+offset/2), (float)((y_position*offset)+offset/2));

        //spawn centipede body segments if it is the start of the game
        if (startOfGame)
        {
            std::cout << "I need to create " << bodySegments << " body objects" << std::endl;
            spawn_body(bodySegments);
        }
    }

void CentipedeHead::move_right()
{
    //pos.x += centipede_speed;
    x_position += centipede_speed;
}

void CentipedeHead::move_left()
{
    //pos.x -= centipede_speed;
    x_position -= centipede_speed;
}

void CentipedeHead::move_up()
{
    //pos.y -= offset;
    y_position += offset;
}

void CentipedeHead::move_down()
{
    //pos.y =+ offset;
    y_position -= offset;
    //auto check = get_Yposition();
    //if (check > 504) {y_position = 504;move_up();}
}

float CentipedeHead::get_Xposition() const
{
   // return pos.x;
   return x_position;
}

float CentipedeHead::get_Yposition() const
{
    //return pos.y;
    return y_position;
}

float CentipedeHead::get_centipedeSpeed() const
{
    return centipede_speed;
}

void CentipedeHead::set_Xposition(float position)
{
    //pos.x = position;
    x_position = position;
}

void CentipedeHead::set_Yposition(float position)
{
    //pos.y = position
    y_position = position;
}

void CentipedeHead::setNextBodySegment(CentipedeBody* ptr)
{
    this -> next = ptr;
}

bool CentipedeHead::get_down() const
{
    return down;
}

bool CentipedeHead::get_up () const
{
    return up;
}

bool CentipedeHead::get_left() const
{
    return left;
}

bool CentipedeHead::get_right() const
{
    return right;
}

void CentipedeHead::spawn_body(int bodySegments)
{
    //if there are body segments to be spawned
    if (bodySegments > 0)
    {
        //create body segments according to specified number.
        // Model body segments with linked list of body objects
        body_ptr = new CentipedeBody(x_position + 1, y_position, this);
        CentipedeBody* iter = body_ptr;
        iter -> setHead(this);
        iter -> setBodySegmentInfront(NULL);

        while (bodySegments > 0)
        {
            //if this is the 1st body segment
            if (iter -> GetBodySegmentInfront() == NULL)
            {
                iter ->setNextBodySegment(new CentipedeBody(iter ->get_Xpos()+offset, y_position, this));
                //update the next segment to b the new segment in front (since it is the only one)
                iter ->GetNextBodySegment()->setBodySegmentInfront(iter);

                //connect 1st segment with the head
                iter ->GetHead()->setNextBodySegment(iter);

                std::cout << "created 1st segment" << std::endl;
            }
            //else this is a body segment in the middle or tail.
            else
            {

                std::cout << "created 2nd segment" << std::endl;
                iter ->setNextBodySegment(new CentipedeBody(iter->get_Xpos()+offset, y_position, NULL));
                iter ->GetNextBodySegment() ->setBodySegmentInfront(iter);
                head_ptr = NULL;
            }

            //update iterator
            iter = iter ->GetNextBodySegment();
            iter ->setNextBodySegment(iter);
            bodySegments--;
        }

    }
}

void CentipedeHead::Update()
{
    counter2++;
    if (down | up)
    {
        counter++;
    }
    else
    {
        counter = 0;
    }

    if(counter2 >= offset/2)
    {
        //need to check if there is a mushroom on left or right of centipede
        check_mushroom();
        counter2 = 0;
        //if there is body segment, keep on updating
        if(next != NULL)
        {
            //need to update the body
            next ->update_body();
        }
    }
    //update the head accordingly
    mark_movement();
    //set sprites accordingly
    //set sprite positions accordingly
}

void CentipedeHead::mark_movement()
{
    if (down)
    {
        if (isMovingRight)
        {
            //rotate sprite accordingly
        }
        else
        {
            //rotate sprite accordingly
        }
        move_down();
    }

    else if (up)
    {
        if (isMovingRight)
        {
            //rotate sprite
        }
        else
        {
            //rotate  sprite
        }
        move_up();
    }

    else if (left)
    {
        move_left();
    }

    else if (right)
    {
        move_right();
    }
}

void CentipedeHead::check_mushroom()
{
    int new_xpos = (int)(pos.x/offset);
    int new_ypos = (int)(pos.y/offset);

    //if centipede is moving down screen
    if (isMovingDown)
    {
        if (left) // centipede moving left
        {
            if ((mushGridPtr ->isMushroom(new_ypos, new_xpos - 1)) | (pos.x <= offset))//mush at the next position or has hit wall
            {
                down = true;
                left = false;
                isMovingLeft = true;
            }
        }

        if (right) //centipede moving to the right
        {
            if ((mushGridPtr ->isMushroom(new_ypos, new_xpos + 1)) | (pos.x >= (windowWidth - offset))) //centipede hit right wall or mush on right
            {
                down = true;
                right = false;
                isMovingRight = true;
            }
        }

        if (down & (counter >= offset/2))
        {
            if (pos.y < windowHeight) //has not reached screen bottom
            {
                if (isMovingRight)
                {
                    down = false;
                    left = true;
                    isMovingRight = false;
                }

                if (isMovingLeft)
                {
                    down = false;
                    right = true;
                    isMovingLeft = false;
                }
            }
            else
            {

                isMovingDown = false;
                isMovingUp = true;
                down = false;

                if (isMovingLeft)
                {
                    right = true;
                    isMovingLeft = false;
                }

                else if (isMovingRight)
                {
                    left = true;
                    isMovingRight = false;
                }
            }

        }
    }

    else if (isMovingUp)
    {
        if (left)
        {
            if ((mushGridPtr ->isMushroom(new_ypos, new_xpos -1 )) | (pos.x <= offset))
            {
                up = true;
                left = false;
                isMovingLeft = true;
            }
        }

        if (right)
        {
            if ((mushGridPtr ->isMushroom(new_ypos, new_xpos - 1)) | (pos.x >= windowWidth - offset))
            {
                up = true;
                right = false;
                isMovingRight = true;
            }
        }

        if (up & (counter >= offset/2))
        {
            if (pos.y > 400)
            {
                if (isMovingRight)
                {
                    up = false;
                    left = true;
                    isMovingRight = false;
                }

                if (isMovingLeft)
                {
                    up = false;
                    right = true;
                    isMovingLeft = false;
                }
            }

            else
            {
                isMovingDown = true;
                isMovingUp = false;
                up = false;
                if (isMovingLeft)
                {
                    right = true;
                    isMovingLeft = false;
                }
                else if (isMovingRight)
                {
                    left = true;
                    isMovingRight = false;
                }
            }
        }
    }

}

