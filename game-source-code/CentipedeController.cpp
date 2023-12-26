#include "CentipedeController.h"

CentipedeController::CentipedeController():
    playerArea_upBound{376},
    deathFramePeriod{0.04f}
{
    load_resources();
}

void CentipedeController::update_centipede(vector<shared_ptr<Centipede>>& centipede_objectVector,
        vector<shared_ptr<sf::Sprite>>& centipedeSprite_vector,vector<shared_ptr<MushroomField>>& mushField)
{
    auto centipedeObject_iter = centipede_objectVector.begin();
    auto centipedeSprite_iter = centipedeSprite_vector.begin();

    while (centipedeObject_iter != centipede_objectVector.end())
    {
        if((centipedeObject_iter + 1) != centipede_objectVector.end())
        {
            auto pos = (((*(centipedeObject_iter +1))->get_position().x) - (*centipedeObject_iter)->get_position().x);
            if((pos > 16) || (pos < -16))
            {
                (*(centipedeObject_iter + 1)) -> setHead(true);
            }
        }

        (*centipedeObject_iter) -> incrementCounter2();

        bool up_ = (*centipedeObject_iter) -> getUp();
        bool down_ = (*centipedeObject_iter) -> getDown();
        if(up_ || down_)
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

        if ((*centipedeObject_iter)->isInDeathAnimation())
        {
            updateSegmentTexture(*centipedeSprite_iter, *centipedeObject_iter);
        }
        else
        {
            Movement((*centipedeObject_iter), (*centipedeSprite_iter));
            auto pos_ = (*centipedeObject_iter)->get_position();
            (*centipedeSprite_iter)->setPosition(pos_);
            animation.Animate((*centipedeObject_iter));
        }

        ++centipedeObject_iter;
        ++centipedeSprite_iter;
    }
}

void CentipedeController::checkFor_mushroom(shared_ptr<Centipede>& centipede_ptr, 
    vector<shared_ptr<MushroomField>>& mushField)
{
    auto pos_ = centipede_ptr -> get_position();
    int newX = (int)(pos_.x/offset);
    int newY = (int)(pos_.y/offset);
    auto wasGoingDown = centipede_ptr -> getWasMovingDown();
    auto wasGoingUp = centipede_ptr -> getWasMovingUp();
    sf::Vector2f mushPosition;
    bool isMushroom = false;
    auto isPoisoned = false;
    auto left = centipede_ptr->getLeft();

    for (auto& mushroom : mushField)
    {
        mushPosition.x = mushroom->get_Xpos();
        mushPosition.y = mushroom->get_Ypos();

        sf::Vector2f segmentPos = pos_;
        segmentPos.y = pos_.y - Tile_offset;

        if (left) segmentPos.x = pos_.x - offset;

        //Difference between mushroom and segment positions
        auto mushSegmentPosDiff = abs(segmentPos.x - mushPosition.x);
        if (mushPosition == segmentPos || (mushSegmentPosDiff <= 0.01f && segmentPos.y == mushPosition.y))
        {
            isMushroom = true;
            isPoisoned = mushroom->getIsPoisoned();
            break;
        }
    }

    if(wasGoingDown)
    {
        auto left_ = centipede_ptr ->getLeft();
        if(left_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if(isMushroom || (pos_.x < Tile_offset) || (centipede_poisoned))
            {
                centipede_ptr -> setDown(true);
                centipede_ptr -> setLeft(false);
                centipede_ptr -> setWasMovingLeft(true);
            }

            //See if there is a poisoned mushroom on the left
            if(isMushroom)
            {
                if(((newX) > 0) && isPoisoned)
                {
                    (centipede_ptr) -> setToPoisoned();
                }
            }
        }

        auto right_ = centipede_ptr -> getRight();
        if(right_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if(isMushroom || (pos_.x >= windowWidth - Tile_offset) || (centipede_poisoned))
            {
                (centipede_ptr) -> setDown(true);
                (centipede_ptr) -> setRight(false);
                (centipede_ptr) -> setWasMovingRight(true);
            }

            if(isMushroom)
            {
                if((newX > 0) && isPoisoned)
                {
                    (centipede_ptr) -> setToPoisoned();
                }
            }
        }

        auto down_ = centipede_ptr -> getDown();
        auto counter_ = centipede_ptr -> get_counter();
        if(down_ && (counter_ >= 8))
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
            if (isMushroom || (pos_.x < Tile_offset) || (centipede_poisoned))
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
            if((pos_.x >= windowWidth - Tile_offset) || (centipede_poisoned) || isMushroom)

            {
                centipede_ptr -> setUp(true);
                centipede_ptr -> setRight(false);
                centipede_ptr -> setWasMovingRight(true);
            }
        }

        auto up_ = centipede_ptr -> getUp();
        auto counter_ = centipede_ptr -> get_counter();
        if (up_ && (counter_>= 8))
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

void CentipedeController::Movement(shared_ptr<Centipede>& centipede_ptr, shared_ptr<sf::Sprite>& centSprite_ptr)
{
    auto down_ = centipede_ptr -> getDown();
    auto up_ = centipede_ptr -> getUp();
    auto left_ = centipede_ptr -> getLeft();
    auto right_ = centipede_ptr -> getRight();
    auto wasMovingLeft = centipede_ptr -> getWasMovingLeft();
    auto wasMovingRight = centipede_ptr -> getWasMovingRight();
    centipede_ptr->setRotation(0.0f);

    sf::Vector2f segmentPos = centipede_ptr->get_position();
    centSprite_ptr->setPosition(segmentPos);

    if(down_)
    {
        if(wasMovingRight)
        {
            centSprite_ptr->rotate(22.5f);
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
    updateSegmentTexture(centSprite_ptr, centipede_ptr);
}

void CentipedeController::load_resources()
{
    //centipede resources
    head1_t.loadFromFile("resources/head1.png");
    head2_t.loadFromFile("resources/head2.png");
    head3_t.loadFromFile("resources/head3.png");
    head4_t.loadFromFile("resources/head4.png");
    head5_t.loadFromFile("resources/head5.png");
    head6_t.loadFromFile("resources/head6.png");
    head7_t.loadFromFile("resources/head7.png");
    head8_t.loadFromFile("resources/head8.png");

    body1_t.loadFromFile("resources/body1.png");
    body2_t.loadFromFile("resources/body2.png");
    body3_t.loadFromFile("resources/body3.png");
    body4_t.loadFromFile("resources/body4.png");
    body5_t.loadFromFile("resources/body5.png");
    body6_t.loadFromFile("resources/body6.png");
    body7_t.loadFromFile("resources/body7.png");
    body8_t.loadFromFile("resources/body8.png");

    death1_t.loadFromFile("resources/death1.png");
    death2_t.loadFromFile("resources/death2.png");
    death3_t.loadFromFile("resources/death3.png");
    death4_t.loadFromFile("resources/death4.png");
    death5_t.loadFromFile("resources/death5.png");
    death6_t.loadFromFile("resources/death6.png");
}

void CentipedeController::updateSegmentTexture(shared_ptr<sf::Sprite>& segment_sprite,
    shared_ptr<Centipede>& centipede_segment)
{
    if (centipede_segment->isInDeathAnimation())
    {
        auto time = centipede_segment->getAnimationTime();

        if (time <= deathFramePeriod)
        {
            segment_sprite->setTexture(death1_t);
            return;
        }
        if (time > deathFramePeriod && time <= 2 * deathFramePeriod)
        {
            segment_sprite->setTexture(death2_t);
            return;
        }
        if (time > 2 * deathFramePeriod && time <= 3 * deathFramePeriod)
        {
            segment_sprite->setTexture(death3_t);
            return;
        }
        if (time > 3 * deathFramePeriod && time <= 4 * deathFramePeriod)
        {
            segment_sprite->setTexture(death4_t);
            return;
        }
        if (time > 4 * deathFramePeriod && time <= 5 * deathFramePeriod)
        {
            segment_sprite->setTexture(death5_t);
            return;
        }
        if (time > 5 * deathFramePeriod && time <= 6 * deathFramePeriod)
        {
            segment_sprite->setTexture(death6_t);
            return;
        }
        if (time > 6 * deathFramePeriod)
        {
            centipede_segment->destroy_object();
            return;
        }
    }
    auto isHead = centipede_segment->getHead();
    auto counter = centipede_segment->get_anime_loop();
    if (isHead)
    {
        switch (counter)
        {
        case 0:
        case 1:
        case 2:
            segment_sprite->setTexture(head1_t);
            break;
        case 3:
        case 4:
        case 5:
            segment_sprite->setTexture(head2_t);
            break;
        case 6:
        case 7:
        case 8:
            segment_sprite->setTexture(head3_t);
            break;
        case 9:
        case 10:
        case 11:
            segment_sprite->setTexture(head4_t);
            break;
        case 12:
        case 13:
        case 14:
            segment_sprite->setTexture(head5_t);
            break;
        case 15:
        case 16:
        case 17:
            segment_sprite->setTexture(head6_t);
            break;
        case 18:
        case 19:
        case 20:
            segment_sprite->setTexture(head7_t);
            break;
        case 21:
            segment_sprite->setTexture(head8_t);
            break;
        default:
            break;
        }

        return;
    }

    switch (counter)
    {
    case 0:
    case 1:
    case 2:
        segment_sprite->setTexture(body1_t);
        break;
    case 3:
    case 4:
    case 5:
        segment_sprite->setTexture(body2_t);
        break;
    case 6:
    case 7:
    case 8:
        segment_sprite->setTexture(body3_t);
        break;
    case 9:
    case 10:
    case 11:
        segment_sprite->setTexture(body4_t);
        break;
    case 12:
    case 13:
    case 14:
        segment_sprite->setTexture(body5_t);
        break;
    case 15:
    case 16:
    case 17:
        segment_sprite->setTexture(body6_t);
        break;
    case 18:
    case 19:
    case 20:
        segment_sprite->setTexture(body7_t);
        break;
    case 21:
        segment_sprite->setTexture(body8_t);
        break;
    default:
        break;
    }
}
