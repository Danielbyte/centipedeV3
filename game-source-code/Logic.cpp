#include "Logic.h"

Logic::Logic():
    counter{0},
    playerArea_upBound{376},
    MushCollidedWith_bullet{false},
    shotCent_segments{0}, //Number of shot segment pieces initially zero
    created_scorpion{false}
{
    LaserShots_object = std::make_shared<LaserShots>(LaserShots(0, -1.f, 8.f));
    auto centipede_ptr = std::make_unique<Centipede>(Centipede());
    centipedeSpeed = centipede_ptr ->getCentipede_speed();
}

void Logic::update_player(Sprite& player_sprite)
{
    auto x = player_object.get_Xposition();
    auto y = player_object.get_Yposition();

    player_sprite.setPosition(x,y);
}

void Logic::updateLaserShots(vector<shared_ptr<Sprite>>& bullet_vector)
{

    vector2f direction;
    float laser_speed = LaserShots_object ->getLaser_speed();
    direction = LaserShots_object ->getBullet_direction();

    auto laserIterator = bullet_vector.begin();
    while (laserIterator != bullet_vector.end())
    {
        (*laserIterator) -> move(laser_speed*direction);

        ++laserIterator;
    }
}

void Logic::create_centipede(bool _isHead, int numbOfBody_segments, vector<shared_ptr<Sprite>>& centipedeSprite_vector)
{
    isHead = _isHead;
    bodySegmentsTo_spawn = numbOfBody_segments;


    if (isHead) //centipede head that is being constructed
    {
        ismovingUp = false;
        ismovingDown = false;
        moveDown = false;
        moveUp = false;
        //update_counter = 1;

        auto centipede_object = std::make_shared<Centipede>(Centipede());
        pos = centipede_object ->get_position();
        centipede_object ->setHead(true);
        centipede_objectVector.push_back(centipede_object);

        //Centipede Sprite setUp
        auto centipede_sprite = std::make_shared<Sprite>(Sprite());
        if (!centipede_texture.loadFromFile("resources/centipede_head.png")) throw CouldNotLoadPicture{};
        centipede_sprite -> setOrigin(vector2f(X_enemy_size/2.0f, Y_enemy_size/2.0f));
        centipede_sprite -> setTexture(centipede_texture);
        centipede_sprite -> setTextureRect(intRect(0, 0, 16, 16));
        //auto index = centipede_objectVector.size() - 1; // get the position of centipede body/head segment
        centipede_sprite -> setPosition(pos);
        centipedeSprite_vector.push_back(centipede_sprite);
        spawn_behind(centipedeSprite_vector);
    }

    else //it is a body segment
    {

        //initialize body segment sprite
        auto centipedeBody_sprite = std::make_shared<Sprite>(Sprite());
        if(!centipedeBody_texture.loadFromFile("resources/centipede_body.png")) throw CouldNotLoadPicture{};
        centipedeBody_sprite -> setOrigin(vector2f(centipedeBody_size/2.0f, centipedeBody_size/2.0f));
        centipedeBody_sprite -> setTexture(centipedeBody_texture);
        centipedeBody_sprite -> setTextureRect(intRect(0,0,16,16));
        auto index = centipede_objectVector.size() - 1;
        //std::cout << index + 1 << std::endl;
        centipedeBody_sprite -> setPosition((centipede_objectVector).at(index) -> get_position());
        //std::cout << "loaded sprite" <<std::endl;
        centipedeSprite_vector.push_back(centipedeBody_sprite);

    }

    return;
}

void Logic::update_centipede(vector<shared_ptr<Sprite>>& centipedeSprite_vector)
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
        if(counter2_ >= 8)
        {
            checkFor_mushroom(*centipedeObject_iter);
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

void Logic::checkFor_mushroom(shared_ptr<Centipede>& centipede_ptr)
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
            if((mushField->isMushroom(newY, newX - 1)) | (pos_.x < offset) | (centipede_poisoned))
            {
                centipede_ptr -> setDown(true);
                centipede_ptr -> setLeft(false);
                centipede_ptr -> setWasMovingLeft(true);
            }
            //See if there is a poisoned mushroom on the left
            if(mushField -> mushArray[newY][newX - 1] != NULL)
            {
                auto isMushPoisoned = mushField -> mushArray[newY][newX - 1] -> getIsPoisoned();
                if(((newX - 1) > 0) && isMushPoisoned)
                {
                    (centipede_ptr) -> setToPoisoned();
                }
            }
        }

        auto right_ = centipede_ptr -> getRight();
        if(right_)
        {
            auto centipede_poisoned = centipede_ptr -> getIsCentipedePoisoned();
            if((mushField->isMushroom(newY,newX + 1)) | (pos_.x >= (windowWidth - offset)) | (centipede_poisoned))
            {
                (centipede_ptr) -> setDown(true);
                (centipede_ptr) -> setRight(false);
                (centipede_ptr) -> setWasMovingRight(true);
            }

            if(mushField -> mushArray[newY][newX + 1] != NULL)
            {
                auto isMushPoisoned = mushField -> mushArray[newY][newX + 1] -> getIsPoisoned();
                if(((newX + 1) > 0) && (isMushPoisoned))
                {
                    (centipede_ptr) -> setToPoisoned();
                }
            }
        }

        auto down_ = centipede_ptr -> getDown();
        auto counter_ = centipede_ptr -> get_counter();
        if(down_ & (counter_ >= 1))
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
            if ((mushField -> isMushroom(newY, newX - 1)) | (pos_.x <= offset) | (centipede_poisoned))
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
            if((mushField -> isMushroom(newY, newX + 1)) | (pos_.x >= (windowWidth - offset)) | (centipede_poisoned))
            {
                centipede_ptr -> setUp(true);
                centipede_ptr -> setRight(false);
                centipede_ptr -> setWasMovingRight(true);
            }
        }

        auto up_ = centipede_ptr -> getUp();
        auto counter_ = centipede_ptr -> get_counter();
        if (up_ & (counter_>= 1))
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

void Logic::Movement(shared_ptr<Centipede>& centipede_ptr, shared_ptr<Sprite>& centSprite_ptr)
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

shared_ptr<MushroomFieldController> Logic::GetMushGridPtr() const
{
    return mushField;
}

void Logic::collisionBetween_mushAndPlayer(Sprite& player_sprite)
{
    vector2d player_pos;
    vector2d mushroom_pos;
    for (int row = 0; row < 32; row++)
    {
        for (int col =0; col < 30; col++)
        {
            if(mushField -> isMushroom(row, col))
            {
                auto isPlayerMovingUp = player_object.getPlayer_movement(Direction::Up);
                auto isPlayerMovingDown = player_object.getPlayer_movement(Direction::Down);
                auto isPlayerMovingRight = player_object.getPlayer_movement(Direction::Right);
                auto isPlayerMovingLeft = player_object.getPlayer_movement(Direction::Left);

                mushroom_pos.x = (float)(col*offset);
                mushroom_pos.y = (float) (row*offset);

                if (isPlayerMovingLeft)
                {
                    auto _offset = 10;
                    player_pos.x = player_object.get_Xposition() - _offset;
                }

                else
                {
                    auto horizontal_offset = 9;
                    player_pos.x = player_object.get_Xposition() - horizontal_offset;
                }

                if (isPlayerMovingUp)
                {
                    auto _offset = 10;
                    player_pos.y = player_object.get_Yposition() - _offset;
                }

                else
                {
                    auto _offset = 5;
                    player_pos.y = player_object.get_Yposition() - _offset;
                }

                auto isCollided = collision.CheckCollision(player_pos, player_size, mushroom_pos, mushroom_size);

                auto PlayerLeftSide = player_pos.x;
                auto PlayerRightSide = PlayerLeftSide + player_size;
                auto PlayerTopSide = player_pos.y;
                auto PlayerBottomSide = PlayerTopSide + player_size;

                auto mushLeftSide = mushroom_pos.x;
                auto mushRightSide = mushLeftSide + mushroom_size;
                auto mushTopSide = mushroom_pos.y;
                auto mushBottomSide = mushTopSide + mushroom_size;

                if(isCollided)
                {
                    //std::cout << "Player collided with mush!!" << std::endl;
                    //player_object.setPlayer_speed(0);
                    /*if (isPlayerMovingRight)
                    {

                        player_sprite.setPosition(mushLeftSide - player_size, player_pos.y);
                    }
                    if (isPlayerMovingLeft)
                    {
                        player_sprite.setPosition(mushRightSide, player_pos.y);
                    }
                    if(isPlayerMovingDown)
                    {
                        player_sprite.setPosition(player_pos.x, mushTopSide - mushroom_size);
                    }
                    if(isPlayerMovingUp)
                    {
                        player_sprite.setPosition(player_pos.x, mushBottomSide);
                    }*/
                }
            }
        }
    }

    //collision between player and centipede
    for (auto& centipede_segment : centipede_objectVector)
    {
        vector2d player_pos_;
        vector2d centipede_pos;

        player_pos_.x = player_object.get_Xposition();
        player_pos_.y = player_object.get_Yposition();

        centipede_pos.x = (centipede_segment) ->get_position().x;
        centipede_pos.y = (centipede_segment) ->get_position().y;

        auto isCollided = collision.CheckCollision(player_pos_, player_size, centipede_pos, centipedeBody_size);

        if (isCollided)
        {
            //decrement player lives
            player_object.decrement_lives();
            //reset player position
            vector2f playerPos;
            playerPos.x = 240;
            playerPos.y = 376 ;
            //update the player object position
            player_object.set_Xposition(playerPos.x);
            player_object.set_Yposition(playerPos.y);
            //Update the player sprite
            player_sprite.setPosition(vector2f(playerPos));

            //update player status. dead or alive.
            auto remainingLives = player_object.getPlayer_lives();
            if(remainingLives == 0)
            {
                player_object.setPlayer_state(false);
            }
            return;
        }
    }

}

void Logic::collisionBetweenBulletsAndObjects (vector<shared_ptr<Sprite>>& laser, vector<shared_ptr<Sprite>>& centipedeSprite_vector)
{
    vector2d bulletPos;
    vector2d objectPos;
    auto laserIter = laser.begin();
    while (laserIter != laser.end())
    {
        //collision between  bullet and mushroom
        for (int row = 0; row < 32; row++)
        {
            for (int col = 0; col < 30; col++)
            {
                if (mushField -> isMushroom(row, col))
                {
                    objectPos.x = col*offset;
                    objectPos.y = row*offset;
                    bulletPos.x = (*laserIter) -> getPosition().x;
                    bulletPos.y = (*laserIter) -> getPosition().y;
                    auto MushCollidedWith_bullet = collision.isCollidedWithBullet(bulletPos, bullet_size/8, objectPos, mushroom_size);
                    if (MushCollidedWith_bullet)
                    {

                        mushField -> mushArray[row][col] -> decrementMush_health();
                        if ((mushField -> mushArray[row][col] -> getMush_health()) == 0)
                        {
                            //std::cout << "Dead"<<std::endl;
                            mushField -> mushArray[row][col] = NULL;
                        }

                        if( laserIter != laser.end())
                        {
                            laser.erase(laserIter);
                            return;
                        }
                    }
                }
            }
        }
        ++laserIter;
    }

    //collision between bullet and centipede
    auto iter2 = laser.begin();
    while (iter2 != laser.end())
    {
        for (auto& centipedeObject : centipede_objectVector)
        {
            vector2d bulletSprite_pos;
            vector2d centipedeObject_pos;

            //current position of laser bullet
            bulletSprite_pos.x = (*iter2) -> getPosition().x;
            bulletSprite_pos.y = (*iter2) -> getPosition().y;

            //updated position of centipede segment
            centipedeObject_pos.x = (centipedeObject) -> get_position().x;
            centipedeObject_pos.y = (centipedeObject) -> get_position().y;

            auto iscollided = collision.isCollidedWithBullet(bulletSprite_pos, bullet_size/offset, centipedeObject_pos, centipedeBody_size);
            if (iscollided)
            {
                //set body segment to inactive
                (centipedeObject) -> setSegment_status(false);
            }

        }
        ++iter2;
    }
    //Time to delete dead segment
    //This is the part where we get to to spawn a mushroom
    auto centObject_iter = centipede_objectVector.begin();
    auto centSprite_iter = centipedeSprite_vector.begin();
    auto laserIter_ = laser.begin();
    while (centObject_iter != centipede_objectVector.end())
    {
        if (((*centObject_iter) ->getSegment_status()) == false)
        {
            //update number of killed bodies
            ++shotCent_segments;

            auto newCent_sprite = ++centSprite_iter;
            //decrement the iterator.
            --centSprite_iter;
            //if it is not the tail
            if (newCent_sprite != centipedeSprite_vector.end())
            {
                (*newCent_sprite) -> setOrigin(vector2f(centipedeBody_size/2.f, centipedeBody_size/2.f));
                (*newCent_sprite) -> setTexture(centipede_texture);
                // set to head
                auto body_segment_behind = (centObject_iter + 1);
                (*body_segment_behind) -> setHead(true);
            }
            //capture position to spawn mushroom
            vector2f posToSpawnMushroom;
            posToSpawnMushroom = (*centObject_iter) ->get_position();
            int newXpos = (int)(posToSpawnMushroom.x/offset);
            int newYpos = (int)(posToSpawnMushroom.y/offset);

            //spawn mushroom.
            mushField -> SpawnMushroomAt_position(newYpos, newXpos);
            centipede_objectVector.erase(centObject_iter);
            centipedeSprite_vector.erase(centSprite_iter);
            //error handling if there are no bullets
            if (!laser.empty())
            {
                laser.erase(laserIter_);
                return;
            }
        }
        else
        {
            ++centObject_iter;
            ++centSprite_iter;
            ++laserIter_;
        }
    }

}

void Logic::spawn_behind(vector<shared_ptr<Sprite>>& CentipdeSprite_vector)
{
    //create a new centipede body object
    bool _ishead = false;
    while (bodySegmentsTo_spawn > 0)
    {
        shared_ptr<Centipede>body_ptr(new Centipede());
        pos.x += offset;
        body_ptr ->set_position(pos);
        bodySegmentsTo_spawn--;
        centipede_objectVector.push_back(body_ptr);
        //std::cout << _ishead << std::endl;
        create_centipede(_ishead, bodySegmentsTo_spawn, CentipdeSprite_vector);
    }
}

void Logic::create_bullet(vector<shared_ptr<Sprite>>& bullet)
{
    //bullet object
    vector2f bullet_pos;
    bullet_pos.x = player_object.get_Xposition();
    bullet_pos.y = player_object.get_Yposition();

    //bullet sprite setup
    auto bullet_sprite = std::make_shared<Sprite>(Sprite());
    if(!bullet_texture.loadFromFile("resources/bullet.png")) throw CouldNotLoadPicture{};
    bullet_sprite ->setTexture(bullet_texture);
    bullet_sprite ->setPosition(bullet_pos);
    auto bullet_offset = 22;
    bullet_sprite ->setOrigin(bullet_size/2, bullet_offset);
    bullet.push_back(bullet_sprite);
}

int Logic::getKilled_segments() const
{
    return shotCent_segments;
}

vector2f Logic::create_scorpion()
{
    auto _pos = scorpion.create_scorpion(centipede_objectVector);
    return _pos;
}

bool Logic::canSpawn_scorpion()
{
    //std::cout << "Time1 " << scorpion_watch.getTimeElapsed() <<std::endl;

    if(scorpion_watch.getTimeElapsed() > scorpion.getScorpion_spawnRate())
    {
        //if 10 seconds has elapsed, spawn scorpion
        scorpion_watch.restart();
        scorpion.setIfCanSpawn_scorpion(true);
        created_scorpion = true;

    }
    else
    {
        scorpion.setIfCanSpawn_scorpion(false);
    }

    if (!scorpion.getIfOffScreen())
    {
        //std::cout << "Scorp moving!!" << std::endl;
        auto pos_ = scorpion.getScorpion_position();
        ChangeToPoison(pos_);
    }

    return scorpion.getIfCanSpawn_scorpion();
}

void Logic::update_scorpion(shared_ptr<Sprite>& scorpion_)
{
    if (scorpion_watch2.getTimeElapsed() > scorpion.getScorpion_spawnRate())
    {
        scorpion.update(scorpion_,scorpion_watch2.getTimeElapsed());

    }
}

void Logic::ChangeToPoison(vector2f pos_)
{
    int xPos = (int)(pos_.x/offset);
    int yPos = (int)(pos_.y/offset);
    if(mushField ->isMushroom(yPos, xPos))
    {
        //std::cout << "Change to poison!!" << std::endl;
        mushField -> mushArray[yPos][xPos] -> changeToPoison();
    }
}

//free up resources
Logic::~Logic()
{
    LaserShots_object.reset();
    centipede_objectVector.clear();
}
