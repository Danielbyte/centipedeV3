#include "Logic.h"

Logic::Logic():
    playerArea_upBound{376},
    MushCollidedWith_bullet{false},
    shotCent_segments{0}, //Number of shot segment pieces initially zero
    created_scorpion{false},
    canSpawnSpider{false},
    score{0},
    inPlayerDeathAnimation{false},
    canMendMushrooms{false},
    segmentsShot{0}
{
    LaserShots_object = std::make_shared<LaserShots>(LaserShots(0, -1.f, 8.f));
    if (!bullet_texture.loadFromFile("resources/bullet.png")) throw CouldNotLoadPicture{};
}

void Logic::update_player(sf::Sprite& player_sprite)
{
    auto x = player_object.get_Xposition();
    auto y = player_object.get_Yposition();

    player_sprite.setPosition(x,y);
}

void Logic::updateLaserShots(vector<shared_ptr<sf::Sprite>>& bullet_vector)
{

    sf::Vector2f direction;
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

void Logic::create_centipede(bool _isHead, int numbOfBody_segments, vector<shared_ptr<sf::Sprite>>& centipedeSprite_vector)
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
        auto centipede_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
        if (!centipede_texture.loadFromFile("resources/centipede_head.png")) throw CouldNotLoadPicture{};
        centipede_sprite -> setOrigin(sf::Vector2f(X_enemy_size/2.0f, Y_enemy_size/2.0f));
        centipede_sprite -> setTexture(centipede_texture);
        centipede_sprite -> setTextureRect(sf::IntRect(0, 0, 16, 16));
        //auto index = centipede_objectVector.size() - 1; // get the position of centipede body/head segment
        centipede_sprite -> setPosition(pos);
        centipedeSprite_vector.push_back(centipede_sprite);
        spawn_behind(centipedeSprite_vector);
    }

    else //it is a body segment
    {

        //initialize body segment sprite
        auto centipedeBody_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
        if(!centipedeBody_texture.loadFromFile("resources/centipede_body.png")) throw CouldNotLoadPicture{};
        centipedeBody_sprite -> setOrigin(sf::Vector2f(centipedeBody_size/2.0f, centipedeBody_size/2.0f));
        centipedeBody_sprite -> setTexture(centipedeBody_texture);
        centipedeBody_sprite -> setTextureRect(sf::IntRect(0,0,16,16));
        auto index = centipede_objectVector.size() - 1;
        //std::cout << index + 1 << std::endl;
        centipedeBody_sprite -> setPosition((centipede_objectVector).at(index) -> get_position());
        //std::cout << "loaded sprite" <<std::endl;
        centipedeSprite_vector.push_back(centipedeBody_sprite);

    }

    return;
}

void Logic::update_centipede(vector<shared_ptr<sf::Sprite>>& centipedeSprite_vector, 
    vector<shared_ptr<MushroomField>>& mushField)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    centipede_controller.update_centipede(centipede_objectVector,centipedeSprite_vector,mushField);
}

void Logic::update_shot_centipede_segments(vector<shared_ptr<sf::Sprite>>& centipede_sprites,
    vector<shared_ptr<MushroomField>>& mushroom_field)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    centipede_controller.update_centipede(shot_centipede_segments, centipede_sprites,
        mushroom_field);
    
    auto segment_sprite = centipede_sprites.begin();
    auto segment = shot_centipede_segments.begin();

    while (segment != shot_centipede_segments.end())
    {
        if ((*segment)->CanDestroy())
        {
            shot_centipede_segments.erase(segment);
            centipede_sprites.erase(segment_sprite);
        }
        else
        {
            ++segment_sprite;
            ++segment;
        }
    }
}

void Logic::create_mushrooms(vector<shared_ptr<MushroomField>>& mushroom_objects, 
    vector<std::shared_ptr<sf::Sprite>>& mushroom_sprites)
{
   int percentage_chance = 13;
   srand((unsigned int)time(NULL));
   for (auto row = 2; row < 32-2; row++)
   {
     for (auto col =0; col < 30; col++)
     {
         //generate a random number between 1 and 100
         auto frequency = (rand() % 100) + 1;

         if (frequency <= percentage_chance)
         {
                shared_ptr<MushroomField>mushroom_ptr = std::make_shared<MushroomField>(MushroomField(col, row));
                auto xPos = mushroom_ptr->get_Xpos();
                auto yPos = mushroom_ptr->get_Ypos();
                shared_ptr<sf::Sprite>mushroom_sprite = std::make_shared<sf::Sprite>();
                mushroom_sprite->setOrigin(0.0f, 0.0f);
                mushroom_sprite->setPosition(xPos, yPos);
                mushroom_resource->update_sprite(mushroom_ptr->getIsPoisoned(), mushroom_ptr->getMush_health(),
                    mushroom_sprite);
                mushroom_objects.push_back(mushroom_ptr);
                mushroom_sprites.push_back(mushroom_sprite);
         }
     }
   }
}

void Logic::collision_between_mush_and_spider(bool isTest,vector<shared_ptr<MushroomField>>& mushField, 
    vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    auto mushroom_iter = mushField.begin();
    auto mushroom_sprite = mushroom_sprites.begin();
    while (mushroom_iter != mushField.end())
    {
        if (!spider_object_vector.empty())
        {
            //This vector always contains one spider
            auto spider_iter = spider_object_vector.begin();
            sf::Vector2f mushPos;
            sf::Vector2f spiderPos;
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
                    sound_manager->playSpiderMunchSound();
                    mushField.erase(mushroom_iter);
                    mushroom_sprites.erase(mushroom_sprite);
                    return;
                }

            }
        }
        ++mushroom_iter;
        ++mushroom_sprite;
    }
}

void Logic::collisionBetween_mushAndPlayer(sf::Sprite& player_sprite,
    vector<shared_ptr<MushroomField>>& mushField)
{
    sf::Vector2f player_pos;
    sf::Vector2f mushroom_pos;
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


void Logic::collision_between_centipede_and_player(sf::Sprite& player_sprite, vector<shared_ptr<sf::Sprite>>& segment_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    //collision between player and centipede
    for (auto& centipede_segment : centipede_objectVector)
    {
        sf::Vector2f player_pos_;
        sf::Vector2f centipede_pos;

        player_pos_.x = player_sprite.getPosition().x - Tile_offset;
        player_pos_.y = player_sprite.getPosition().y - Tile_offset;

        centipede_pos.x = ((centipede_segment) ->get_position().x) - Tile_offset;
        centipede_pos.y = ((centipede_segment) ->get_position().y) - Tile_offset;

        auto isCollided = collision.collision_detect(player_pos_,playerWidth,playerHeight,centipede_pos,centWidth,centHeight);

        if (isCollided && !inPlayerDeathAnimation)
        {
            segment_sprites.clear();
            centipede_objectVector.clear();
            //decrement player lives
            player_object.decrement_lives();
            sound_manager->playPlayerDeathSound();
            player_object.restartAnimationWatch();
            inPlayerDeathAnimation = true;

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

void Logic::collision_between_player_and_spider(sf::Sprite& player_sprite, vector<shared_ptr<sf::Sprite>>& spider_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    sf::Vector2f playePos;
    sf::Vector2f spiderPos;

    playePos.x = player_object.get_Xposition() - Tile_offset;
    playePos.y = player_object.get_Yposition() - Tile_offset;

    auto spider_iter = spider_object_vector.begin();
    if(!spider_object_vector.empty())
    {
        spiderPos = (*spider_iter) -> get_position();
        auto isCollided = collision.collision_detect(playePos,playerWidth,playerHeight,spiderPos,spiderWidth,spiderHeight);
        if (isCollided && !inPlayerDeathAnimation)
        {
            spider_object_vector.clear();
            spider_sprites.clear();

            player_object.restartAnimationWatch();
            inPlayerDeathAnimation = true;

            player_object.decrement_lives();
            sound_manager->playPlayerDeathSound();

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

void Logic::collisionBetweenBulletsAndObjects(vector<shared_ptr<sf::Sprite>>& laser, 
    vector<shared_ptr<sf::Sprite>>& centipedeSprite_vector, vector<shared_ptr<MushroomField>>& mushField,
    vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    sf::Vector2f bulletPos;
    sf::Vector2f objectPos;
    auto laserIter = laser.begin();
    while (laserIter != laser.end())
    {
        //collision between  bullet and mushroom
        auto mushroom_ptr = mushField.begin();
        auto mushroom_sprite = mushroom_sprites.begin();
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
                mushroom_resource->update_sprite((*mushroom_ptr)->getIsPoisoned(), (*mushroom_ptr)->getMush_health(), *mushroom_sprite);
                if (((*mushroom_ptr)->getMush_health()) == 0)
                {
                    mushField.erase(mushroom_ptr);
                    mushroom_sprites.erase(mushroom_sprite);
                    score += mushroomPoints;
                }
          
                laser.erase(laserIter);
                return;
            }
            ++mushroom_ptr;
            ++mushroom_sprite;
        }                
        ++laserIter;
    }
}

void Logic::collision_between_centipede_and_bullet(vector<shared_ptr<sf::Sprite>>& laser, vector<shared_ptr<sf::Sprite>>& centipedeSprite_vector,
    vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites,
    vector<shared_ptr<sf::Sprite>>& shot_segments)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    //collision between bullet and centipede
    auto iter2 = laser.begin();
    while (iter2 != laser.end())
    {
        auto segment_sprite = centipedeSprite_vector.begin();
        for (auto& centipedeObject : centipede_objectVector)
        {
            sf::Vector2f bulletSprite_pos;
            sf::Vector2f centipedeObject_pos;

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
                ++segmentsShot;
                //set body segment to inactive
                (centipedeObject) -> setSegment_status(false);
                centipedeObject->startDeathAnimation();

                sound_manager->playEnemyDeathSound();

                shot_centipede_segments.push_back(centipedeObject);
                shot_segments.push_back(*segment_sprite);
                if(centipedeObject -> getHead())
                {
                    score += headPoints;
                }
                else
                {
                    score += bodyPoints;
                }
                laser.erase(iter2);
                return;
            }
            ++segment_sprite;
        }
        ++iter2;
    }
    delete_segment_and_spawn_mushroom(centipedeSprite_vector, mushField, mushroom_sprites);
    update_shot_centipede_segments(shot_segments, mushField);
}

void Logic::delete_segment_and_spawn_mushroom(vector<shared_ptr<sf::Sprite>>& centipedeSprite_vector,
    vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
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
                // set to head
                auto body_segment_behind = (centObject_iter + 1);
                (*body_segment_behind) -> setHead(true);
            }

                //capture position to spawn mushroom
                sf::Vector2f posToSpawnMushroom;
                posToSpawnMushroom = (*centObject_iter) ->get_position();
                int newXpos = (int)(posToSpawnMushroom.x/offset);
                int newYpos = (int)(posToSpawnMushroom.y/offset);

                //spawn mushroom.
                shared_ptr<MushroomField>mushroom=std::make_shared<MushroomField>(MushroomField
                (newXpos, newYpos));

                auto xPos = mushroom->get_Xpos();
                auto yPos = mushroom->get_Ypos();
                shared_ptr<sf::Sprite>mushroom_sprite = std::make_shared<sf::Sprite>();
                mushroom_sprite->setOrigin(0.0f, 0.0f);
                mushroom_sprite->setPosition(xPos, yPos);
                mushroom_resource->update_sprite(mushroom->getIsPoisoned(), mushroom->getMush_health(), mushroom_sprite);
                mushField.push_back(mushroom);
                mushroom_sprites.push_back(mushroom_sprite);

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

void Logic::collision_btwn_bullet_and_spider(vector<shared_ptr<sf::Sprite>>& bullet, vector<shared_ptr<sf::Sprite>>& spider_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    auto spider_iter = spider_object_vector.begin();
    auto spiderSprite_iter = spider_sprites.begin();
    auto inDeathAnimation = (*spider_iter)->isInDeathAnimation();
    if(!spider_object_vector.empty() && !inDeathAnimation)
    {
        auto bullet_iter = bullet.begin();
        while (bullet_iter != bullet.end())
        {
            sf::Vector2f bulletPos;
            sf::Vector2f spiderPos;
            bulletPos.x = ((*bullet_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_iter) -> getPosition().y) - Tile_offset;

            spiderPos = (*spider_iter) -> get_position();

            auto isCollided = collision.collision_detect(bulletPos,bulletWidth,bulletHeight,spiderPos,spiderWidth,spiderHeight);
    
            if(isCollided)
            {
                //play death sound
                sound_manager->playEnemyDeathSound();
                //update score
                score += spiderPoints;
                bullet.erase(bullet_iter);
                (*spider_iter)->startDeathAnimation();
            }
            else
            {
                ++bullet_iter;
            }
        }
    }

    auto spider_sprite = spider_sprites.begin();
    auto spider_ = spider_object_vector.begin();
    while (spider_ != spider_object_vector.end())
    {
        if ((*spider_)->CanDestroy())
        {
            spider_sprites.erase(spider_sprite);
            spider_object_vector.erase(spider_);
        }
        else
        {
            ++spider_;
            ++spider_sprite;
        }
    }
}

void Logic::collision_between_bullet_and_flea(vector<shared_ptr<sf::Sprite>>& bullet_sprite, vector<shared_ptr<sf::Sprite>>& flea_sprite)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    auto flea_obj_iter = flea_object.begin();
    auto flea_sprite_iter = flea_sprite.begin();
    auto inDeathAnimation = (*flea_obj_iter)->isInDeathAnimation();
    if(!flea_object.empty() && !inDeathAnimation)
    {
        auto bullet_iter = bullet_sprite.begin();
        while(bullet_iter != bullet_sprite.end())
        {
            sf::Vector2f fleaPos;
            sf::Vector2f bulletPos;

            bulletPos.x = ((*bullet_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_iter) -> getPosition().y) - Tile_offset;

            fleaPos = (*flea_sprite_iter) -> getPosition();
            auto isCollided = collision.collision_detect(bulletPos,bulletWidth,bulletHeight,fleaPos,fleaWidth,fleaHeight);
            if(isCollided)
            {
                (*flea_obj_iter) -> decrement_health();
                auto flea_health = (*flea_obj_iter) -> get_flea_health();
                bullet_sprite.erase(bullet_iter);
                if(flea_health == 0)
                {
                    sound_manager->playEnemyDeathSound();
                    score += fleaPoints;
                    (*flea_obj_iter)->startDeathAnimation();
                }

                else
                {
                    //flea must increase in speed
                    (*flea_obj_iter) -> double_flea_speed();
                }
            }
            else
            {
                ++bullet_iter;
            }  
        }
    }

    flea_obj_iter = flea_object.begin();
    flea_sprite_iter = flea_sprite.begin();
    while (flea_obj_iter != flea_object.end())
    {
        if ((*flea_obj_iter)->CanDestroy())
        {
            flea_object.clear();
            flea_sprite.clear();
        }
        else
        {
            ++flea_obj_iter;
            ++flea_sprite_iter;
        }
    }
}

void Logic::collision_between_player_and_flea(sf::Sprite& player_sprite, vector<shared_ptr<sf::Sprite>>& flea_sprite)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    sf::Vector2f playePos;
    sf::Vector2f fleaPos;

    playePos.x = player_object.get_Xposition() - Tile_offset;
    playePos.y = player_object.get_Yposition() - Tile_offset;

    auto flea_iter = flea_object.begin();
    if(!flea_object.empty())
    {
        fleaPos = (*flea_iter) -> get_position();
        auto isCollided = collision.collision_detect(playePos,playerWidth,playerHeight,fleaPos,fleaWidth,fleaHeight);
        if (isCollided && !inPlayerDeathAnimation)
        {
            flea_object.clear();
            flea_sprite.clear();

            player_object.restartAnimationWatch();
            inPlayerDeathAnimation = true;

            player_object.decrement_lives();
            sound_manager->playPlayerDeathSound();

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


void Logic::collision_between_bullet_and_bomb(vector<shared_ptr<sf::Sprite>>& bullet_sprite, vector<shared_ptr<sf::Sprite>>& bomb_sprite,
        vector<shared_ptr<sf::Sprite>>& spider_sprite, vector<shared_ptr<sf::Sprite>>& centipede_sprite,
        vector<shared_ptr<sf::Sprite>>& scorpion_sprite, sf::Sprite& player_sprite, bool& playerBombed, vector<shared_ptr<sf::Sprite>>& flea_sprite,
    vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    //First we need to have bombs on the field
    auto bullet_sprite_iter = bullet_sprite.begin();
    while (bullet_sprite_iter != bullet_sprite.end())
    {
        for (auto& bomb : vector_of_bomb_objects)
        {
            sf::Vector2f bulletPos;
            sf::Vector2f bombPos;
            bulletPos.x = ((*bullet_sprite_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_sprite_iter) -> getPosition().y) - Tile_offset;

            bombPos.x = (bomb -> get_position().x) - Tile_offset;
            bombPos.y = (bomb -> get_position().y) - Tile_offset;
            auto isCollided = collision.collision_detect(bombPos,bomb1Width,bomb1Height,bulletPos,bulletWidth,bulletHeight);

            if(isCollided)
            {
                sound_manager->playBombDetonationSound();
                //Mark the bomb to be updated in the update function
                bomb -> setExplosion(true);
                bullet_sprite.erase(bullet_sprite_iter);
                return;
            }
        }
        ++bullet_sprite_iter;
    }

    bomb_controller.Explosion(vector_of_bomb_objects, bomb_sprite, mushField, mushroom_sprites, spider_object_vector,spider_sprite,centipede_objectVector,
                              centipede_sprite,scorpion_object_vector,scorpion_sprite,player_object, playerBombed, player_sprite, flea_object,
                              flea_sprite,score, segmentsShot);

    if (playerBombed)
    {
        sound_manager->playPlayerDeathSound();
        player_object.restartAnimationWatch();
        inPlayerDeathAnimation = true;
    }
        
}

void Logic::collision_between_bullet_and_scorpion(vector<shared_ptr<sf::Sprite>>& bulletSpriteVector,vector<shared_ptr<sf::Sprite>>& scorpion_sprite)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    auto scorpion_iter = scorpion_object_vector.begin();
    auto scorpion_sprite_iter = scorpion_sprite.begin();
    auto inDeathAnimation = (*scorpion_iter)->isInDeathAnimation();
    if(!scorpion_object_vector.empty() && !inDeathAnimation)
    {
        auto bullet_iter = bulletSpriteVector.begin();
        while (bullet_iter != bulletSpriteVector.end())
        {
            sf::Vector2f bulletPos;
            sf::Vector2f scorpionPos;
            bulletPos.x = ((*bullet_iter) -> getPosition().x) - bullet_offset;
            bulletPos.y = ((*bullet_iter) -> getPosition().y) - Tile_offset;

            scorpionPos = (*scorpion_iter) -> getScorpion_position();

            auto isCollided = collision.collision_detect(bulletPos,bulletWidth,bulletHeight,scorpionPos,scorpion_width,scorpion_height);
            if(isCollided)
            {
                sound_manager->playEnemyDeathSound();
                //update score
                score += scorpionPoints;
                bulletSpriteVector.erase(bullet_iter);
                (*scorpion_iter)->startDeathAnimation();
            }
            else
            {
                ++bullet_iter;
            }
        }
    }

    scorpion_iter = scorpion_object_vector.begin();
    scorpion_sprite_iter = scorpion_sprite.begin();
    while (scorpion_iter != scorpion_object_vector.end())
    {
        if ((*scorpion_iter)->CanDestroy())
        {
            scorpion_object_vector.erase(scorpion_iter);
            scorpion_sprite.erase(scorpion_sprite_iter);
        }
        else
        {
            ++scorpion_iter;
            ++scorpion_sprite_iter;
        }
    }
}

void Logic::spawn_behind(vector<shared_ptr<sf::Sprite>>& CentipdeSprite_vector)
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

void Logic::create_bullet(vector<shared_ptr<sf::Sprite>>& bullet)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    //bullet object
    sf::Vector2f bullet_pos;
    bullet_pos.x = player_object.get_Xposition();
    bullet_pos.y = player_object.get_Yposition() - Tile_offset;

    //bullet sprite setup
    auto bullet_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    bullet_sprite ->setTexture(bullet_texture);
    bullet_sprite ->setPosition(bullet_pos);
    bullet_sprite ->setOrigin(bulletWidth/2, bulletHeight/2);
    bullet.push_back(bullet_sprite);
}

int Logic::getKilled_segments() const
{
    return shotCent_segments;
}

sf::Vector2f Logic::create_scorpion()
{
    auto scorpion_object = std::make_shared<Scorpion>();
    auto _pos = control_scorpion.position_to_spawn_scorpion();
    (scorpion_object) -> set_position(_pos);
    scorpion_object_vector.push_back(scorpion_object);
    return _pos;
}

bool Logic::canSpawn_scorpion()
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return false;

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

void Logic::update_scorpion(vector<shared_ptr<sf::Sprite>>& scorpion, vector<shared_ptr<MushroomField>>& mushField,
    vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    //only update if we have a scorpion
    if (!scorpion.empty())
    {
        control_scorpion.update_scorpion(scorpion_object_vector,scorpion,mushField, mushroom_sprites);
    }
}

bool Logic::getIfCanSpawnSpider()
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return false;

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

sf::Vector2f Logic::create_spider()
{
    auto spider_object = std::make_shared<Spider>();
    auto pos_ = spider_object -> get_position();
    spider_object_vector.push_back(spider_object);
    return pos_;
}

void Logic::update_spider(vector<shared_ptr<sf::Sprite>>& spider_sprite)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    if (!spider_sprite.empty())
    {
        spider_control.update_spider(spider_sprite, spider_object_vector);
    }
}

bool Logic::getIfCanSpawnBomb()
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return false;

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

sf::Vector2f Logic::create_bomb()
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
    if (inPlayerDeathAnimation || canMendMushrooms)
        return false;

    auto canSpawnFlea = flea_control.set_if_can_spawn_flea(mushField);
    return canSpawnFlea;
}

sf::Vector2f Logic::create_flea()
{
    auto flea = std::make_shared<Flea>();
    sf::Vector2f pos_;
    pos_ = flea_control.generate_spawn_position();
    flea -> set_position(pos_);
    flea_object.push_back(flea);
    return pos_;
}

void Logic::update_flea(vector<shared_ptr<sf::Sprite>>& flea_sprite, vector<shared_ptr<MushroomField>>& mushField,
    vector<shared_ptr<sf::Sprite>>& mushroom_sprites)
{
    if (inPlayerDeathAnimation || canMendMushrooms)
        return;

    flea_control.update_flea(flea_object,flea_sprite,mushField, mushroom_sprites);
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

bool Logic::isInPlayerDeathAnimation() const
{
    return inPlayerDeathAnimation;
}

void Logic::updatePlayerTexture(sf::Sprite& player_sprite)
{
    player_object.updatePlayerTexture(inPlayerDeathAnimation, canMendMushrooms, player_sprite, mushroom_mend_watch);
}

void Logic::refresh_game_world(vector<shared_ptr<MushroomField>>& mushrooms, vector<shared_ptr<sf::Sprite>>& mushroom_sprites,
    vector<shared_ptr<sf::Sprite>>& centipede_sprites, vector<shared_ptr<sf::Sprite>>& spider_sprites,
    vector<shared_ptr<sf::Sprite>>& scorpion_sprite, vector<shared_ptr<sf::Sprite>>& flea_sprite)
{
    auto mushrooms_mended = 0;
    auto time_elapsed = mushroom_mend_watch->getTimeElapsed();

    if (!canMendMushrooms || time_elapsed < 0.15f)
        return;

    mushroom_mend_watch->restart();

    auto mushroom_sprite = mushroom_sprites.begin();
    for (auto& mushroom : mushrooms)
    {
        if (mushroom->getMush_health() < 4)
        {
            centipede_objectVector.clear();
            centipede_sprites.clear();
            segmentsShot = 0;

            spider_object_vector.clear();
            spider_sprites.clear();

            scorpion_object_vector.clear();
            scorpion_sprite.clear();

            flea_object.clear();
            flea_sprite.clear();

            sound_manager->playMendMushroomSound();
            mushroom->resetMushroomHealth();
            mushroom_resource->update_sprite(mushroom->getIsPoisoned(),mushroom->getMush_health(), *mushroom_sprite);
            ++mushrooms_mended;
            return;
        }
        ++mushroom_sprite;
    }

    if (mushrooms_mended == 0)
    {
        canMendMushrooms = false;
        segmentsShot = 0;

        //restart game
        centipede_objectVector.clear();
        centipede_sprites.clear();
        auto segmentsToSpawn = 11;
        create_centipede(true, segmentsToSpawn, centipede_sprites);

        spider_object_vector.clear();
        spider_sprites.clear();

        scorpion_object_vector.clear();
        scorpion_sprite.clear();

        flea_object.clear();
        flea_sprite.clear();
    }
}

int Logic::getNumberOfShotSegments() const
{
    return segmentsShot;
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
    shot_centipede_segments.clear();
}
