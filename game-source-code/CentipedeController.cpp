#include "CentipedeController.h"

CentipedeController::CentipedeController():
    playerArea_upBound{376}
    {}

void CentipedeController::update_centipede(vector<shared_ptr<Centipede>>& centipede_objectVector,
                                           vector<shared_ptr<Sprite>>& centipedeSprite_vector, shared_ptr<MushroomFieldController>& mushField)
{
    auto centipedeObject_iter = centipede_objectVector.begin();
    auto centipedeSprite_iter = centipedeSprite_vector.begin();

    while (centipedeObject_iter != centipede_objectVector.end())
    {
        (*centipedeObject_iter) -> incrementCounter2();

        bool up_ = (*centipedeObject_iter) -> getUp();
        bool down_ = (*centipedeObject_iter) -> getDown();
        if(up_ | down_)
        {
            (*centipedeObject_iter) -> increment_counter();
        }
        else
        {
            (*centipedeObject_iter) -> reset_counter();
        }

        auto counter2_ = (*centipedeObject_iter) -> getCounter2();
        if(counter2_ >= 1)
        {
            checkFor_mushroom(*centipedeObject_iter, mushField);
            (*centipedeObject_iter) -> resetCounter2();
        }

        Movement((*centipedeObject_iter),(*centipedeSprite_iter));
        auto pos_ = (*centipedeObject_iter) -> get_position();
        (*centipedeSprite_iter) -> setPosition(pos_);
        animation.Animate((*centipedeObject_iter), (*centipedeSprite_iter));

        ++centipedeObject_iter;
        ++centipedeSprite_iter;
    }
}

void CentipedeController::checkFor_mushroom(shared_ptr<Centipede>& centipede_ptr, shared_ptr<MushroomFieldController>& mushField)
{
    auto pos_ = centipede_ptr -> get_position();
    int newX = (int)(pos_.x/offset);
    int newY = (int)(pos_.y/offset);
    auto wasGoingDown = centipede_ptr -> getWasMovingDown();
    auto wasGoingUp = centipede_ptr -> getWasMovingUp();

    if(wasGoingDown)
    {
        auto left_ = centipede_ptr ->getLeft();
        if(left_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if(((mushField->isMushroom(newY, newX))) | (pos_.x < Tile_offset) | (centipede_poisoned))
            {
                centipede_ptr -> setDown(true);
                centipede_ptr -> setLeft(false);
                centipede_ptr -> setWasMovingLeft(true);
            }

            //See if there is a poisoned mushroom on the left
            if(mushField -> mushArray[newY][newX] != NULL)
            {
                auto isMushPoisoned = mushField -> mushArray[newY][newX] -> getIsPoisoned();
                if(((newX) > 0) && isMushPoisoned)
                {
                    (centipede_ptr) -> setToPoisoned();
                }
            }
        }

        auto right_ = centipede_ptr -> getRight();
        if(right_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if(((mushField->isMushroom(newY,newX))) | (pos_.x >= windowWidth - Tile_offset) | (centipede_poisoned))
            {
                (centipede_ptr) -> setDown(true);
                (centipede_ptr) -> setRight(false);
                (centipede_ptr) -> setWasMovingRight(true);
            }

            if(mushField -> mushArray[newY][newX] != NULL)
            {
                auto isMushPoisoned = mushField -> mushArray[newY][newX] -> getIsPoisoned();
                if((newX > 0) && (isMushPoisoned))
                {
                    (centipede_ptr) -> setToPoisoned();
                }
            }
        }

        auto down_ = centipede_ptr -> getDown();
        auto counter_ = centipede_ptr -> get_counter();
        if(down_ & (counter_ >= 8))
        {
            if(pos_.y < windowHeight - 8)
            {
                auto wasGoingRight = centipede_ptr -> getWasMovingRight();
                if(wasGoingRight)
                {
                    centipede_ptr -> setDown(false);
                    centipede_ptr -> setLeft(true);
                    centipede_ptr -> setWasMovingRight(false);
                }
                auto wasGoingLeft = centipede_ptr ->getWasMovingLeft();
                if(wasGoingLeft)
                {
                    centipede_ptr -> setDown(false);
                    centipede_ptr -> setRight(true);
                    centipede_ptr -> setWasMovingLeft(false);
                }
            }

            else
            {
                centipede_ptr -> setWasMovingDown(false);
                centipede_ptr -> setWasMovingUp(true);
                centipede_ptr -> setDown(false);
                centipede_ptr -> cure_from_poison();

                auto wasGoingLeft = centipede_ptr -> getWasMovingLeft();
                if(wasGoingLeft)
                {
                    centipede_ptr -> setRight(true);
                    centipede_ptr -> setWasMovingLeft(false);
                }

                auto wasGoingRight = centipede_ptr -> getWasMovingRight();
                if(wasGoingRight)
                {
                    centipede_ptr -> setLeft(true);
                    centipede_ptr -> setWasMovingRight(false);
                }
            }
        }
        wasGoingUp = centipede_ptr -> getWasMovingUp();
    }

    else if(wasGoingUp)
    {
        auto left_ = centipede_ptr -> getLeft();
        if(left_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if ((mushField -> isMushroom(newY, newX)) | (pos_.x < Tile_offset) | (centipede_poisoned))
            {
                //std::cout << "Came here! " <<std::endl;
                centipede_ptr -> setUp(true);
                centipede_ptr -> setLeft(false);
                centipede_ptr -> setWasMovingLeft(true);
            }
        }

        auto right_ = centipede_ptr -> getRight();
        if(right_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if((pos_.x >= windowWidth - Tile_offset) | (centipede_poisoned) | (mushField -> isMushroom(newY, newX)))

            {
                centipede_ptr -> setUp(true);
                centipede_ptr -> setRight(false);
                centipede_ptr -> setWasMovingRight(true);
            }
        }

        auto up_ = centipede_ptr -> getUp();
        auto counter_ = centipede_ptr -> get_counter();
        if (up_ & (counter_>= 8))
        {
            if(pos_.y > playerArea_upBound)
            {
                auto wasGoingRight = centipede_ptr -> getWasMovingRight();
                if(wasGoingRight)
                {
                    centipede_ptr -> setUp(false);
                    centipede_ptr -> setLeft(true);
                    centipede_ptr -> setWasMovingRight(false);
                }

                auto wasGoingLeft = centipede_ptr -> getWasMovingLeft();
                if(wasGoingLeft)
                {
                    centipede_ptr -> setUp(false);
                    centipede_ptr -> setRight(true);
                    centipede_ptr -> setWasMovingLeft(false);
                }
            }

            else
            {
                centipede_ptr -> setWasMovingDown(true);
                centipede_ptr -> setWasMovingUp(false);
                centipede_ptr -> setUp(false);

                auto wasGoingLeft = centipede_ptr -> getWasMovingLeft();
                auto wasGoingRight = centipede_ptr -> getWasMovingRight();
                if (wasGoingLeft)
                {
                    centipede_ptr -> setRight(true);
                    centipede_ptr -> setWasMovingLeft(false);
                }

                else if (wasGoingRight)
                {
                    centipede_ptr -> setLeft(true);
                    centipede_ptr -> setWasMovingRight(false);
                }
            }
        }
    }
}

void CentipedeController::Movement(shared_ptr<Centipede>& centipede_ptr, shared_ptr<Sprite>& centSprite_ptr)
{
    auto down_ = centipede_ptr -> getDown();
    auto up_ = centipede_ptr -> getUp();
    auto left_ = centipede_ptr -> getLeft();
    auto right_ = centipede_ptr -> getRight();
    auto wasMovingLeft = centipede_ptr -> getWasMovingLeft();
    auto wasMovingRight = centipede_ptr -> getWasMovingRight();

    if(down_)
    {
        if(wasMovingRight)
        {
            centSprite_ptr -> rotate(22.5);
        }
        else
        {
            centSprite_ptr -> rotate(-22.5);
        }

        centipede_ptr -> move_down();
    }

    else if(up_)
    {
        if(wasMovingLeft)
        {
            centSprite_ptr -> rotate(-22.5);
        }
        else
        {
            centSprite_ptr -> rotate(22.5);
        }

        centipede_ptr -> move_up();
    }

    else if(left_)
    {
        centipede_ptr -> move_left();
    }

    else if(right_)
    {
        centipede_ptr -> move_right();
    }
}