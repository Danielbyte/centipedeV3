#include "Logic.h"

Logic::Logic():
    playerArea_upBound{376},
    MushCollidedWith_bullet{false},
    shotCent_segments{0}, //Number of shot segment pieces initially zero
    created_scorpion{false},
    canSpawnSpider{false},
    score{0}
{
    LaserShots_object = std::make_shared<LaserShots>(LaserShots(0, -1.f, 8.f));
    //auto centipede_ptr = std::make_shared<Centipede>(Centipede());
    //centipedeSpeed = centipede_ptr ->getCentipede_speed();
   // isHit = false;
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

        auto position = (*laserIterator) -> getPosition();
        if (position.y < (-bullet_size/2))
        {
            bullet_vector.erase(laserIterator);
            return;
        }

        ++laserIterator;
    }

}

void Logic::create_centipede(bool _isHead, int numbOfBody_segments, vector<shared_ptr<Sprite>>& centipedeSprite_vector)
{
    isHead = _isHead;
    bodySegmentsTo_spawn = numbOfBody_segments;


    if (isHead) //centipede head that is being constructed
    {
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

void Logic::update_centipede(vector<shared_ptr<Sprite>>& centipedeSprite_vector, 
    vector<shared_ptr<MushroomField>>& mushField)
{
    centipede_controller.update_centipede(centipede_objectVector,centipedeSprite_vector,mushField);
}

void Logic::create_mushrooms(vector<shared_ptr<MushroomField>>& mushField)
{
   int percentage_chance = 7;
   srand(time(0));
   for (auto row = 2; row < 32-2; row++)
   {
     for (auto col =0; col < 30; col++)
     {
         //generate a random number between 1 and 100
         auto frequency = (rand() % 100) + 1;

         if (frequency <= percentage_chance)
         {
             //Do not spawn mushroom at this row for proper creation of centipede
            if((row != 0) && (row != 1))
             {
                shared_ptr<MushroomField>mushroom_ptr = std::make_shared<MushroomField>(MushroomField(col, row));
                mushField.push_back(mushroom_ptr);
             }

         }
     }
   }
}

void Logic::collision_between_mush_and_spider(bool isTest,vector<shared_ptr<MushroomField>>& mushField)
{
    auto mushroom_iter = mushField.begin();
    while (mushroom_iter != mushField.end())
    {
        if (!spider_object_vector.empty())
        {
            //This vector always contains one spider
            auto spider_iter = spider_object_vector.begin();
            vector2f mushPos;
            vector2f spiderPos;
            mushPos.x = (*mushroom_iter)->get_Xpos();
            mushPos.y = (*mushroom_iter)->get_Ypos();

            spiderPos = (*spider_iter)->get_position();
            auto isCollided = collision.collision_detect(spiderPos, spiderWidth, spiderHeight, mushPos, mushWidth, mushHeight);
            if (isCollided)
            {
                //Abuti spider should OCCASIONALLY chow SOME of the mushes
                //execute the line below if it is not a test
                auto lunch_time_ = (*spider_iter)->getSpider_lunch_time();
                float luncheon;

                //if it is actual game play
                if (!isTest)
                {
                    spiderIsHungry = (*spider_iter)->getIsHungry();
                    luncheon = lunch_time.getTimeElapsed();
                }
                else //if it is a test case
                {
                    luncheon = lunch_time.getTimeElapsed(dummy);
                }

                if (spiderIsHungry && (luncheon >= lunch_time_))
                {
                    lunch_time.restart();
                    mushField.erase(mushroom_iter);
                    return;
                }

            }
        }
        ++mushroom_iter;
    }
}

void Logic::collisionBetween_mushAndPlayer(Sprite& player_sprite,
    vector<shared_ptr<MushroomField>>& mushField)
{
    vector2f player_pos;
    vector2f mushroom_pos;
    auto mushroom_ptr = mushField.begin();
    while (mushroom_ptr != mushField.end())
    {
        mushroom_pos.x = (*mushroom_ptr)->get_Xpos(); //(float)(col * offset);
        mushroom_pos.y = (*mushroom_ptr)->get_Ypos();//(float)(row * offset);

        player_pos.x = player_object.get_Xposition() - Tile_offset;
        player_pos.y = player_object.get_Yposition() - Tile_offset;

        auto mush_left = (float)mushroom_pos.x;
        auto mush_right = mush_left + mushWidth;
        auto mush_top = mushroom_pos.y - 8;
        auto mush_bottom = mush_top + mushHeight;

        //now time for the whole hulla balloo
        auto isPlayerMovingUp = player_object.getPlayer_movement(Direction::Up);
        auto isPlayerMovingDown = player_object.getPlayer_movement(Direction::Down);
        auto isPlayerMovingRight = player_object.getPlayer_movement(Direction::Right);
        auto isPlayerMovingLeft = player_object.getPlayer_movement(Direction::Left);

        if (isPlayerMovingDown)
        {
            dir1 = Direction::Down;
        }
        if (isPlayerMovingLeft)
        {
            dir1 = Direction::Left;
        }
        if (isPlayerMovingRight)
        {
            dir1 = Direction::Right;
        }
        if (isPlayerMovingUp)
        {
            dir1 = Direction::Up;
        }

        auto speed = player_object.getPlayer_speed();

        if ((dir1 != dir) && (dir != Direction::unknown) && (speed == 0))
        {
            std::cout << "new Direction!" << std::endl;
            player_object.setPlayer_speed(4);
            auto pos_y = player_pos.y;
            auto pos_x = player_pos.x;

            if (isPlayerMovingUp)
            {
                player_object.set_Yposition(pos_y + Tile_offset - 4);
            }
            if (isPlayerMovingDown)
            {
                player_object.set_Yposition(pos_y + Tile_offset + 4);
            }
            if (isPlayerMovingLeft)
            {
                player_object.set_Xposition(pos_x + Tile_offset - 4);
            }
            if (isPlayerMovingRight)
            {
                player_object.set_Xposition(pos_x + Tile_offset + 4);
            }
        }

        auto isCollided = collision.collision_detect(player_pos, playerWidth, playerHeight, mushroom_pos, mushWidth, mushHeight);
        if (isCollided)
        {
            if (isPlayerMovingDown)
            {
                dir = Direction::Down;
            }
            if (isPlayerMovingLeft)
            {
                dir = Direction::Left;
            }
            if (isPlayerMovingRight)
            {
                dir = Direction::Right;
            }
            if (isPlayerMovingUp)
            {
                dir = Direction::Up;
            }
            player_object.setPlayer_speed(0);
        }
        ++mushroom_ptr;
    }
}


void Logic::collision_between_centipede_and_player(Sprite& player_sprite)
{
    //collision between player and centipede
    for (auto& centipede_segment : centipede_objectVector)
    {
        vector2f player_pos_;
        vector2f centipede_pos;

        player_pos_.x = player_sprite.getPosition().x - Tile_offset;
        player_pos_.y = player_sprite.getPosition().y - Tile_offset;

        centipede_pos.x = ((centipede_segment) ->get_position().x) - Tile_offset;
        centipede_pos.y = ((centipede_segment) ->get_position().y) - Tile_offset;

        auto isCollided = collision.collision_detect(player_pos_,playerWidth,playerHeight,centipede_pos,centWidth,centHeight);

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

void Logic::collision_between_player_and_spider(Sprite& player_sprite)
{
    vector2f playePos;
    vector2f spiderPos;

    playePos.x = player_object.get_Xposition() - Tile_offset;
    playePos.y = player_object.get_Yposition() - Tile_offset;

    auto spider_iter = spider_object_vector.begin();
    if(!spider_object_vector.empty())
    {
        spiderPos = (*spider_iter) -> get_position();
        auto isCollided = collision.collision_detect(playePos,playerWidth,playerHeight,spiderPos,spiderWidth,spiderHeight);
        if (isCollided)
        {
            player_object.decrement_lives();
            //reset player position
            vector2f playerPos;
            playerPos.x = 16;
            playerPos.y = 504 ;
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

void Logic::collisionBetweenBulletsAndObjects (vector<shared_ptr<Sprite>>& laser, 
    vector<shared_ptr<Sprite>>& centipedeSprite_vector, vector<shared_ptr<MushroomField>>& mushField)
{
    vector2f bulletPos;
    vector2f objectPos;
    auto laserIter = laser.begin();
    while (laserIter != laser.end())
    {
        //collision between  bullet and mushroom
        auto mushroom_ptr = mushField.begin();
        while (mushroom_ptr != mushField.end())
        {
            objectPos.x = (*mushroom_ptr)->get_Xpos();
            objectPos.y = (*mushroom_ptr)->get_Ypos();
            bulletPos.x = ((*laserIter)->getPosition().x) - bullet_offset;
            bulletPos.y = ((*laserIter)->getPosition().y) - Tile_offset;
            auto MushCollidedWith_bullet = collision.collision_detect(objectPos, mushWidth,
                mushHeight, bulletPos, bulletWidth, bulletHeight);

            if (MushCollidedWith_bullet)
            {

                (*mushroom_ptr)->decrementMush_health();
                if (((*mushroom_ptr)->getMush_health()) == 0)
                {
                    mushField.erase(mushroom_ptr);
                    score += mushroomPoints;
                    laser.erase(laserIter);
                    return;
                }
            }
            ++mushroom_ptr;
        }                
        ++laserIter;
    }
}

void Logic::collision_between_centipede_and_bullet(vector<shared_ptr<Sprite>>& laser, vector<shared_ptr<Sprite>>& centipedeSprite_vector,
    vector<shared_ptr<MushroomField>>& mushField)
{
    //collision between bullet and centipede
    auto iter2 = laser.begin();
    while (iter2 != laser.end())
    {
        for (auto& centipedeObject : centipede_objectVector)
        {
            vector2f bulletSprite_pos;
            vector2f centipedeObject_pos;

            //current position of laser bullet
            bulletSprite_pos.x = ((*iter2) -> getPosition().x) - bullet_offset;
            bulletSprite_pos.y = ((*iter2) -> getPosition().y) - Tile_offset;

            //updated position of centipede segment
            centipedeObject_pos.x = (centipedeObject) -> get_position().x;
            centipedeObject_pos.x = centipedeObject_pos.x - Tile_offset;
            centipedeObject_pos.y = (centipedeObject) -> get_position().y;
            centipedeObject_pos.y = centipedeObject_pos.y - Tile_offset;

            auto iscollided = collision.collision_detect(bulletSprite_pos,bulletWidth,bulletHeight,centipedeObject_pos,centWidth,centHeight);
            if (iscollided)
            {
                //set body segment to inactive
                (centipedeObject) -> setSegment_status(false);
                if(centipedeObject -> getHead())
                {
                    score += headPoints;
                }
                else
                {
                    score += bodyPoints;
                }
                laser.erase(iter2);
                //isHit = true;
                return;
            }
           // else
            //{
             //   isHit = false;
            //}

        }
        ++iter2;
    }
    delete_segment_and_spawn_mushroom(centipedeSprite_vector, mushField);

}

void Logic::delete_segment_and_spawn_mushroom(vector<shared_ptr<Sprite>>& centipedeSprite_vector,
    vector<shared_ptr<MushroomField>>& mushField)
{
    //Time to delete dead segment
    //This is the part where we get to to spawn a mushroom
    auto centObject_iter = centipede_objectVector.begin();
    auto centSprite_iter = centipedeSprite_vector.begin();
    // auto laserIter_ = laser.begin();
    while (centObject_iter != centipede_objectVector.end())
    {
        if (((*centObject_iter) ->getSegment_status()) == false)
        {

            auto newCent_sprite = (centSprite_iter + 1);
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
            shared_ptr<MushroomField>mushroom=std::make_shared<MushroomField>(MushroomField
            (newXpos, newYpos));
       
            centipede_objectVector.erase(centObject_iter);
            centipedeSprite_vector.erase(centSprite_iter);
        }
        else
        {
            ++centObject_iter;
            ++centSprite_iter;
            // ++laserIter_;
        }
    }
}

void Logic::collision_btwn_bullet_and_spider(vector<shared_ptr<Sprite>>& bullet, vector<shared_ptr<Sprite>>& spider)
{
    auto spider_iter = spider_object_vector.begin();
    auto spiderSprite_iter = spider.begin();
    if(!spider_object_vector.empty())
    {
        auto bullet_iter = bullet.begin();
        while (bullet_iter != bullet.end())
        {
            vector2f bulletPos;
            vector2f spiderPos;
            bulletPos.x = ((*bullet_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_iter) -> getPosition().y) - Tile_offset;

            spiderPos = (*spider_iter) -> get_position();

            auto isCollided = collision.collision_detect(bulletPos,bulletWidth,bulletHeight,spiderPos,spiderWidth,spiderHeight);
            if(isCollided)
            {
                //update score
                score += spiderPoints;
                bullet.erase(bullet_iter);
                spider_object_vector.erase(spider_iter);
                spider.erase(spiderSprite_iter);
                return;
            }

            ++bullet_iter;
        }
    }
}

void Logic::collision_between_bullet_and_flea(vector<shared_ptr<Sprite>>& bullet_sprite, vector<shared_ptr<Sprite>>& flea_sprite)
{

    if(!flea_object.empty())
    {
        auto flea_obj_iter = flea_object.begin();
        auto flea_sprite_iter = flea_sprite.begin();
        auto bullet_iter = bullet_sprite.begin();
        while(bullet_iter != bullet_sprite.end())
        {
            vector2f fleaPos;
            vector2f bulletPos;

            bulletPos.x = ((*bullet_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_iter) -> getPosition().y) - Tile_offset;

            fleaPos = (*flea_sprite_iter) -> getPosition();
            auto isCollided = collision.collision_detect(bulletPos,bulletWidth,bulletHeight,fleaPos,fleaWidth,fleaHeight);
            if(isCollided)
            {
                (*flea_obj_iter) -> decrement_health();
                auto flea_health = (*flea_obj_iter) -> get_flea_health();
                if(flea_health == 0)
                {
                    score += fleaPoints;
                    flea_sprite.clear();
                    flea_object.clear();
                    bullet_sprite.erase(bullet_iter);
                    return;
                }

                else
                {
                    //flea must increase in speed
                    (*flea_obj_iter) -> double_flea_speed();
                    bullet_sprite.erase(bullet_iter);
                    return;

                }
            }
            ++bullet_iter;
        }
    }

}

void Logic::collision_between_player_and_flea(Sprite& player_sprite)
{
    vector2f playePos;
    vector2f fleaPos;

    playePos.x = player_object.get_Xposition() - Tile_offset;
    playePos.y = player_object.get_Yposition() - Tile_offset;

    auto flea_iter = flea_object.begin();
    if(!flea_object.empty())
    {
        fleaPos = (*flea_iter) -> get_position();
        auto isCollided = collision.collision_detect(playePos,playerWidth,playerHeight,fleaPos,fleaWidth,fleaHeight);
        if (isCollided)
        {
            player_object.decrement_lives();
            //reset player position
            vector2f playerPos;
            playerPos.x = 16;
            playerPos.y = 504 ;
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


void Logic::collision_between_bullet_and_bomb(vector<shared_ptr<Sprite>>& bullet_sprite, vector<shared_ptr<Sprite>>& bomb_sprite,
        vector<shared_ptr<Sprite>>& spider_sprite, vector<shared_ptr<Sprite>>& centipede_sprite,
        vector<shared_ptr<Sprite>>& scorpion_sprite, Sprite& player_sprite, vector<shared_ptr<Sprite>>& flea_sprite,
    vector<shared_ptr<MushroomField>>& mushField)
{
    //First we need to have bombs on the field
    auto bullet_sprite_iter = bullet_sprite.begin();
    while (bullet_sprite_iter != bullet_sprite.end())
    {
        for (auto& bomb : vector_of_bomb_objects)
        {
            vector2f bulletPos;
            vector2f bombPos;
            bulletPos.x = ((*bullet_sprite_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_sprite_iter) -> getPosition().y) - Tile_offset;

            bombPos.x = (bomb -> get_position().x) - Tile_offset;
            bombPos.y = (bomb -> get_position().y) - Tile_offset;
            auto isCollided = collision.collision_detect(bombPos,bomb1Width,bomb1Height,bulletPos,bulletWidth,bulletHeight);

            if(isCollided)
            {
                //std::cout << "Collided!" << std::endl;
                //Mark the bomb to be updated in the update function
                bomb -> setExplosion(true);
                bullet_sprite.erase(bullet_sprite_iter);
                return;
            }
        }
        ++bullet_sprite_iter;
    }

    bomb_controller.Explosion(vector_of_bomb_objects, bomb_sprite, mushField, spider_object_vector,spider_sprite,centipede_objectVector,
                              centipede_sprite,scorpion_object_vector,scorpion_sprite,player_object,player_sprite, flea_object,
                              flea_sprite,score);
    return;
}

void Logic::collision_between_bullet_and_scorpion(vector<shared_ptr<Sprite>>& bulletSpriteVector,vector<shared_ptr<Sprite>>& scorpion_sprite)
{
    auto scorpion_iter = scorpion_object_vector.begin();
    auto scorpion_sprite_iter = scorpion_sprite.begin();
    if(!scorpion_object_vector.empty())
    {
        auto bullet_iter = bulletSpriteVector.begin();
        while (bullet_iter != bulletSpriteVector.end())
        {
            vector2f bulletPos;
            vector2f scorpionPos;
            bulletPos.x = ((*bullet_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_iter) -> getPosition().y) - Tile_offset;

            scorpionPos = (*scorpion_iter) -> getScorpion_position();

            auto isCollided = collision.collision_detect(bulletPos,bulletWidth,bulletHeight,scorpionPos,scorpion_width,scorpion_height);
            if(isCollided)
            {
                //update score
                score += scorpionPoints;
                bulletSpriteVector.erase(bullet_iter);
                scorpion_object_vector.erase(scorpion_iter);
                scorpion_sprite.erase(scorpion_sprite_iter);
                return;
            }

            ++bullet_iter;
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
    bullet_pos.y = player_object.get_Yposition() - Tile_offset;

    //bullet sprite setup
    auto bullet_sprite = std::make_shared<Sprite>(Sprite());
    if(!bullet_texture.loadFromFile("resources/bullet.png")) throw CouldNotLoadPicture{};
    bullet_sprite ->setTexture(bullet_texture);
    bullet_sprite ->setPosition(bullet_pos);
    bullet_sprite ->setOrigin(bulletWidth/2, bulletHeight/2);
    bullet.push_back(bullet_sprite);
}

int Logic::getKilled_segments() const
{
    return shotCent_segments;
}

vector2f Logic::create_scorpion()
{
    auto scorpion_object = std::make_shared<Scorpion>();
    auto _pos = control_scorpion.position_to_spawn_scorpion();
    (scorpion_object) -> set_position(_pos);
    scorpion_object_vector.push_back(scorpion_object);
    return _pos;
}

bool Logic::canSpawn_scorpion()
{
    if((scorpion_watch.getTimeElapsed() > scorpion.getScorpion_spawnRate()) && (scorpion_object_vector.empty()))
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

    return scorpion.getIfCanSpawn_scorpion();
}

void Logic::update_scorpion(vector<shared_ptr<Sprite>>& scorpion, vector<shared_ptr<MushroomField>>& mushField)
{
    //only update if we have a scorpion
    if (!scorpion.empty())
    {
        control_scorpion.update_scorpion(scorpion_object_vector,scorpion,mushField);
    }
}

bool Logic::getIfCanSpawnSpider()
{
    if(spider_watch.getTimeElapsed() > spider.getSpideSpawnRate())
    {
        //after 10 seconds , restart timer
        spider_watch.restart();
        spider.setIfCanSpawnSpider(true);
    }
    else
    {
        spider.setIfCanSpawnSpider(false);
    }

    return spider.getIfCanSpawnSpider();
}

vector2f Logic::create_spider()
{
    auto spider_object = std::make_shared<Spider>();
    auto pos_ = spider_object -> get_position();
    spider_object_vector.push_back(spider_object);
    return pos_;
}

void Logic::update_spider(vector<shared_ptr<Sprite>>& spider_sprite)
{
    if (!spider_sprite.empty())
    {
        spider_control.update_spider(spider_sprite, spider_object_vector);
    }
}

bool Logic::getIfCanSpawnBomb()
{
    //variable to set when logic should query the
    //bomb controller to create bomb;
    float check_time = 5; //check after every 5 seconds

    //query bomb controller if willing to spawn bomb
    bomb_controller.setIfCanCreateBomb();
    auto canCreateBomb = bomb_controller.getIfCanCreateBomb();

    //only max 4 bombs allowed
    auto number_of_bombs = vector_of_bomb_objects.size();
    auto max_bombs = 4ul;

    if ((bomb_check.getTimeElapsed() >= check_time) && (number_of_bombs < max_bombs) && (canCreateBomb))
    {
        bomb_check.restart();
        return true;
    }

    else
    {
        return false;
    }
}

vector2f Logic::create_bomb()
{
    bomb_controller.generate_position();
    auto pos_ = bomb_controller.getGeneratedPosition();
    auto bomb_object = std::make_shared<DDTBombs>();
    bomb_object -> set_position(pos_);
    vector_of_bomb_objects.push_back(bomb_object);
    return pos_;
}

bool Logic::getIfCanSpawnFlea(vector<shared_ptr<MushroomField>>& mushField)
{
    auto canSpawnFlea = flea_control.set_if_can_spawn_flea(mushField);
    return canSpawnFlea;
}

vector2f Logic::create_flea()
{
    auto flea = std::make_shared<Flea>();
    vector2f pos_;
    pos_ = flea_control.generate_spawn_position();
    flea -> set_position(pos_);
    flea_object.push_back(flea);
    return pos_;
}

void Logic::update_flea(vector<shared_ptr<Sprite>>& flea_sprite, vector<shared_ptr<MushroomField>>& mushField)
{
    flea_control.update_flea(flea_object,flea_sprite,mushField);
}

int Logic::get_score() const
{
    return score;
}

//Dummy functions for Spider Tests
float Logic::get_lunch_time()
{
    return dummy;
}

void Logic::set_lunch(float dummy)
{
    this -> dummy = dummy;
}

void Logic::setSpiderToHungry(bool var)
{
    spiderIsHungry = var;
}

//free up resources
Logic::~Logic()
{
    centipede_objectVector.clear();
    spider_object_vector.clear();
    scorpion_object_vector.clear();
    flea_object.clear();
    LaserShots_object.reset();
    vector_of_bomb_objects.clear();
}
