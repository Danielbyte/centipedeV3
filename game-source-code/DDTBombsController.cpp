#include "DDTBombsController.h"

DDTBombsController::DDTBombsController():
    canCreateBomb{false}
{}

void DDTBombsController::setIfCanCreateBomb()
{
    srand(time(NULL));
    //generate a random number between 1 and 100
    auto decider1 = (rand() % 100) + 1;

    //generate another random number between 1 and 50;
    auto decider2 = (rand() % 50) + 1;


    //generate a bomb if the above two deciders are equal
    //max bombs = 4
    if((decider1 < decider2))
    {
        canCreateBomb = true;
    }
    else
    {
        canCreateBomb = false;
    }
}

bool DDTBombsController::getIfCanCreateBomb() const
{
    return canCreateBomb;
}

void DDTBombsController::generate_position(shared_ptr<MushroomFieldController>& mushField)
{
    auto row = (rand() % 20) + 6;
    auto col =(rand() % 20) + 6;

    pos.x = col*offset;
    pos.y = row*offset;
}

vector2f DDTBombsController::getGeneratedPosition() const
{
    return pos;
}

void DDTBombsController::Explosion(vector<shared_ptr<DDTBombs>>& bombObj, vector<shared_ptr<Sprite>>& bombSprite,
                                   shared_ptr<MushroomFieldController>& mushField, vector<shared_ptr<Spider>>& spiderObj,
                                   vector<shared_ptr<Sprite>>& spiderSprite,vector<shared_ptr<Centipede>>& centipedeobj,
                                   vector<shared_ptr<Sprite>>& centipedeSpite,vector<shared_ptr<Scorpion>>& scorpionObj,
                                   vector<shared_ptr<Sprite>>& scorpion_sprite,Player& player_obj, Sprite& player_sprite,
                                   vector<shared_ptr<Flea>>& fleaObj, vector<shared_ptr<Sprite>>& flea_sprite)
{
    auto bombSprite_iter = bombSprite.begin();
    auto bomb_iter = bombObj.begin();
    while (bomb_iter != bombObj.end())
    {
        if((*bomb_iter) -> getIfcanExplode())
        {
            auto counter = (*bomb_iter) -> get_counter();
            if (counter == 0)
            {
                bomb_texture.loadFromFile("resources/bomb2.png");
                bomb_texture.setSmooth(true);
                (*bombSprite_iter) -> setTexture(bomb_texture);
                (*bombSprite_iter) -> setScale(2,2);
            }

            if (counter == 5)
            {
                bomb_texture.loadFromFile("resources/bomb3.png");
                (*bombSprite_iter) -> setTexture(bomb_texture);
                (*bombSprite_iter) -> setScale(3,3);
            }

            if (counter == 15)
            {
                bomb_texture.loadFromFile("resources/bomb2.png");
                (*bombSprite_iter) -> setTexture(bomb_texture);
                (*bombSprite_iter) -> setScale(2,2);
            }

            if (counter == 20)
            {
                bomb_texture.loadFromFile("resources/bomb3.png");
                (*bombSprite_iter) -> setTexture(bomb_texture);
                (*bombSprite_iter) -> setScale(3,3);
            }

            if (counter == 25)
            {
                bomb_texture.loadFromFile("resources/bomb4.png");
                (*bombSprite_iter) -> setTexture(bomb_texture);
                (*bombSprite_iter) -> setScale(4,4);
                //check collision between explosion and mushroom(final radius)
                explosion_and_mush((*bombSprite_iter), mushField);
                explosion_and_spider((*bombSprite_iter),spiderObj,spiderSprite);
                explosion_and_centipede((*bombSprite_iter),centipedeobj,centipedeSpite);
                explosion_and_scorpion((*bombSprite_iter),scorpionObj,scorpion_sprite);
                explosion_and_player((*bombSprite_iter),player_obj,player_sprite);
            }

            if (counter == 30)
            {

                bombObj.erase(bomb_iter);
                bombSprite.erase(bombSprite_iter);
                return;
            }

            (*bomb_iter) -> increment_counter();

        }
        ++bomb_iter;
        ++bombSprite_iter;
    }
}

void DDTBombsController::explosion_and_mush(shared_ptr<Sprite>& bomb_sprite, shared_ptr<MushroomFieldController>& mushField)
{
    //should kill mushroom within radious
    for (auto row = 0; row < 32; row++)
    {
        for (auto col = 0; col < 30; col++)
        {
            if (mushField->isMushroom(row, col))
            {
                vector2f mushPos;
                vector2f explosion_pos = bomb_sprite -> getPosition();
                explosion_pos.x = explosion_pos.x;
                explosion_pos.y = explosion_pos.y;
                auto explosion_width = bomb_sprite -> getGlobalBounds().width;
                auto explosion_height = bomb_sprite -> getGlobalBounds().height;
                mushPos.x = col*offset;
                mushPos.y = row*offset;
                //void fourth quadrant collisisns
                fourth_quadrant_collisions(mushPos, mushWidth,mushHeight,explosion_pos,explosion_width,explosion_height,row, col, mushField);
                third_quadrant_collisions(mushPos, mushWidth,mushHeight,explosion_pos,explosion_width,explosion_height,row, col, mushField);
                second_quadrant_collisions(mushPos, mushWidth,mushHeight,explosion_pos,explosion_width,explosion_height,row, col, mushField);
                first_quadrant_collisions(mushPos, mushWidth,mushHeight,explosion_pos,explosion_width,explosion_height,row, col, mushField);
            }
        }
    }

    return;
}

void DDTBombsController::explosion_and_spider(shared_ptr<Sprite>& bomb_sprite, vector<shared_ptr<Spider>>& spider_obj,
        vector<shared_ptr<Sprite>>& spider_sprite)
{
    //these vectors will either have one spider object/sprite nothing
    auto spiderObject_iter = spider_obj.begin();
    auto spiderSprite_iter = spider_sprite.begin();
    if(!spider_obj.empty())
    {
        bool isCollided;
        vector2f SpiderPos;
        vector2f explosion_pos;
        SpiderPos = (*spiderSprite_iter) -> getPosition();
        explosion_pos = bomb_sprite -> getPosition();
        auto explosion_width = bomb_sprite -> getGlobalBounds().width;
        auto explosion_height = bomb_sprite -> getGlobalBounds().height;
        isCollided = fourth_quadrant_collisions(SpiderPos, spiderWidth,spiderHeight,explosion_pos,explosion_width,explosion_height, isCollided);
        if(isCollided)
        {
            spider_obj.erase(spiderObject_iter);
            spider_sprite.erase(spiderSprite_iter);
            return;
        }

        isCollided = third_quadrant_collisions(SpiderPos, spiderWidth,spiderHeight,explosion_pos,explosion_width,explosion_height, isCollided);
        if(isCollided)
        {
            spider_obj.erase(spiderObject_iter);
            spider_sprite.erase(spiderSprite_iter);
            return;
        }

        isCollided = second_quadrant_collisions(SpiderPos, spiderWidth,spiderHeight,explosion_pos,explosion_width,explosion_height, isCollided);
        if(isCollided)
        {
            spider_obj.erase(spiderObject_iter);
            spider_sprite.erase(spiderSprite_iter);
            return;
        }

        isCollided = first_quadrant_collisions(SpiderPos, spiderWidth,spiderHeight,explosion_pos,explosion_width,explosion_height, isCollided);
        if(isCollided)
        {
            spider_obj.erase(spiderObject_iter);
            spider_sprite.erase(spiderSprite_iter);
            return;
        }
    }
    return;
}

void DDTBombsController::explosion_and_centipede(shared_ptr<Sprite>& bomb_sprite, vector<shared_ptr<Centipede>>& centipede_obj,
        vector<shared_ptr<Sprite>>& centipede_sprite)
{
    for(auto& segment : centipede_obj)
    {
        bool isCollided;
        vector2f explosion_pos;
        vector2f segment_pos;
        segment_pos.x = (segment -> get_position().x) - Tile_offset;
        segment_pos.y = (segment -> get_position().y) - Tile_offset;
        explosion_pos = bomb_sprite -> getPosition();
        auto explosion_width = bomb_sprite -> getGlobalBounds().width;
        auto explosion_height = bomb_sprite -> getGlobalBounds().height;

        isCollided = first_quadrant_collisions(segment_pos,centWidth,centHeight,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            segment -> is_hit(true);
        }

        isCollided = second_quadrant_collisions(segment_pos,centWidth,centHeight,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            segment -> is_hit(true);
        }

        isCollided = third_quadrant_collisions(segment_pos,centWidth,centHeight,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            segment -> is_hit(true);
        }

        isCollided = fourth_quadrant_collisions(segment_pos,centWidth,centHeight,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            segment -> is_hit(true);
        }

    }

    //The next step is to wipe out all the destroyed centipede segments and update
    auto centipede_obj_iter = centipede_obj.begin();
    auto centipede_sprite_iter = centipede_sprite.begin();
    while(centipede_obj_iter != centipede_obj.end())
    {
        if((*centipede_obj_iter) -> get_is_hit())
        {
            //point to the segment behing
            auto behind_ptr = (centipede_obj_iter + 1);
            if(behind_ptr != centipede_obj.end())
            {
                (*behind_ptr) -> setHead(true);
                //let the centipedeAnimation take care of the sprite
                //since it knows how to update head and bodies respectively.
                //Yaaay!!
            }

            centipede_obj.erase(centipede_obj_iter);
            centipede_sprite.erase(centipede_sprite_iter);
        }

        else
        {
            ++centipede_obj_iter;
            ++centipede_sprite_iter;
        }
    }
}

void DDTBombsController::explosion_and_scorpion(shared_ptr<Sprite>& bomb_sprite,vector<shared_ptr<Scorpion>>& scorpionObj,
        vector<shared_ptr<Sprite>>& scorpion_sprite)
{
    //only execute when we have a spider
    if(!scorpion_sprite.empty())
    {

        bool isCollided;
        vector2f explosion_pos;
        vector2f scorpion_pos;

        //scorpion will always have on object
        auto scorpion_sprite_iter = scorpion_sprite.begin();

        explosion_pos = bomb_sprite -> getPosition();
        scorpion_pos = (*scorpion_sprite_iter) -> getPosition();

        auto explosion_width = bomb_sprite -> getGlobalBounds().width;
        auto explosion_height = bomb_sprite -> getGlobalBounds().height;

        isCollided = first_quadrant_collisions(scorpion_pos,scorpion_width,scorpion_height,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            scorpion_sprite.erase(scorpion_sprite_iter);
            scorpionObj.clear();
            return;
        }

        isCollided = second_quadrant_collisions(scorpion_pos,scorpion_width,scorpion_height,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            scorpion_sprite.erase(scorpion_sprite_iter);
            scorpionObj.clear();
            return;
        }

        isCollided = third_quadrant_collisions(scorpion_pos,scorpion_width,scorpion_height,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            scorpion_sprite.erase(scorpion_sprite_iter);
            scorpionObj.clear();
            return;
        }

        isCollided = fourth_quadrant_collisions(scorpion_pos,scorpion_width,scorpion_height,explosion_pos,explosion_width,explosion_height,isCollided);
        if(isCollided)
        {
            scorpion_sprite.erase(scorpion_sprite_iter);
            scorpionObj.clear();
            return;
        }
    }

    return;
}

void DDTBombsController::explosion_and_player(shared_ptr<Sprite>& bomb_sprite, Player& player_object, Sprite& player_sprite)
{
    bool isCollided;
    vector2f player_pos;
    vector2f explosion_pos;
    explosion_pos = bomb_sprite -> getPosition();
    player_pos = player_sprite.getPosition();
    player_pos.x = player_pos.x - Tile_offset;
    player_pos.y = player_pos.y -Tile_offset;
    auto explosion_width = bomb_sprite -> getGlobalBounds().width;
    auto explosion_height = bomb_sprite -> getGlobalBounds().height;

    isCollided = first_quadrant_collisions(player_pos,playerWidth,playerHeight,explosion_pos,explosion_width,explosion_height,isCollided);
    if(isCollided)
    {
        player_object.decrement_lives();
        auto player_lives = player_object.getPlayer_lives();
        if(player_lives == 0)
        {
            player_object.setPlayer_state(false);
            return;
        }
        else
        {
            vector2f newPos;
            player_object.set_Xposition(240.f);
            player_object.set_Yposition(376.f);
            newPos.x = player_object.get_Xposition();
            newPos.y = player_object.get_Yposition();
            player_sprite.setPosition(newPos);
        }
    }

    isCollided = second_quadrant_collisions(player_pos,playerWidth,playerHeight,explosion_pos,explosion_width,explosion_height,isCollided);
    if(isCollided)
    {
        player_object.decrement_lives();
        auto player_lives = player_object.getPlayer_lives();
        if(player_lives == 0)
        {
            player_object.setPlayer_state(false);
            return;
        }
        else
        {
            vector2f newPos;
            player_object.set_Xposition(240.f);
            player_object.set_Yposition(376.f);
            newPos.x = player_object.get_Xposition();
            newPos.y = player_object.get_Yposition();
            player_sprite.setPosition(newPos);
        }
    }

    isCollided = third_quadrant_collisions(player_pos,playerWidth,playerHeight,explosion_pos,explosion_width,explosion_height,isCollided);
    if(isCollided)
    {
        player_object.decrement_lives();
        auto player_lives = player_object.getPlayer_lives();
        if(player_lives == 0)
        {
            player_object.setPlayer_state(false);
            return;
        }
        else
        {
            vector2f newPos;
            player_object.set_Xposition(240.f);
            player_object.set_Yposition(376.f);
            newPos.x = player_object.get_Xposition();
            newPos.y = player_object.get_Yposition();
            player_sprite.setPosition(newPos);
        }
    }

    isCollided = fourth_quadrant_collisions(player_pos,playerWidth,playerHeight,explosion_pos,explosion_width,explosion_height,isCollided);
    if(isCollided)
    {
        player_object.decrement_lives();
        auto player_lives = player_object.getPlayer_lives();
        if(player_lives == 0)
        {
            player_object.setPlayer_state(false);
            return;
        }
        else
        {
            vector2f newPos;
            player_object.set_Xposition(240.f);
            player_object.set_Yposition(376.f);
            newPos.x = player_object.get_Xposition();
            newPos.y = player_object.get_Yposition();
            player_sprite.setPosition(newPos);
        }
    }
}

//Quadrant collisions(general)
bool DDTBombsController::fourth_quadrant_collisions(vector2f obj1Pos, float obj1Width, float obj1Height,
        vector2f obj2Pos, float obj2Width, float obj2Height, bool& isCollided)
{
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    return isCollided;
}

bool DDTBombsController::third_quadrant_collisions(vector2f obj1Pos, float obj1Width, float obj1Height,
        vector2f obj2Pos, float obj2Width, float obj2Height, bool& isCollided)
{
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    obj2Pos.x = obj2Pos.x - 32;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    return isCollided;
}

bool DDTBombsController::second_quadrant_collisions(vector2f obj1Pos, float obj1Width, float obj1Height,
        vector2f obj2Pos, float obj2Width, float obj2Height, bool& isCollided)
{
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    obj2Pos.x = obj2Pos.x - 32;
    obj2Pos.y = obj2Pos.y - 32;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    return isCollided;
}

bool DDTBombsController::first_quadrant_collisions(vector2f obj1Pos, float obj1Width, float obj1Height,
        vector2f obj2Pos, float obj2Width, float obj2Height, bool& isCollided)
{
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    obj2Pos.y = obj2Pos.y - 32;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    return isCollided;
}

//Quadrant collisions specific to mushrooms
void DDTBombsController::fourth_quadrant_collisions(vector2f obj1Pos,float obj1Width, float obj1Height,
        vector2f obj2Pos,float obj2Width, float obj2Height, int row, int col, shared_ptr<MushroomFieldController>& mushField)
{
    bool isCollided;
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    if(isCollided)
    {
        mushField -> mushArray[row][col] = NULL;
    }

    return;
}

void DDTBombsController::third_quadrant_collisions(vector2f obj1Pos,float obj1Width, float obj1Height,
        vector2f obj2Pos,float obj2Width, float obj2Height, int row, int col, shared_ptr<MushroomFieldController>& mushField)
{

    bool isCollided;
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    obj2Pos.x = obj2Pos.x - 32;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    if(isCollided)
    {
        mushField -> mushArray[row][col] = NULL;
    }

    return;
}

void DDTBombsController::second_quadrant_collisions(vector2f obj1Pos,float obj1Width, float obj1Height,
        vector2f obj2Pos,float obj2Width, float obj2Height, int row, int col, shared_ptr<MushroomFieldController>& mushField)
{

    bool isCollided;
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    obj2Pos.x = obj2Pos.x - 32;
    obj2Pos.y = obj2Pos.y -32;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    if(isCollided)
    {
        mushField -> mushArray[row][col] = NULL;
    }

    return;
}

void DDTBombsController::first_quadrant_collisions(vector2f obj1Pos,float obj1Width, float obj1Height,
        vector2f obj2Pos,float obj2Width, float obj2Height, int row, int col, shared_ptr<MushroomFieldController>& mushField)
{

    bool isCollided;
    obj2Width = obj2Width/2;
    obj2Height = obj2Height/2;
    obj2Pos.y = obj2Pos.y -32;
    isCollided = collision.collision_detect(obj1Pos,obj1Width,obj1Height,obj2Pos,obj2Width,obj2Height);
    if(isCollided)
    {
        mushField -> mushArray[row][col] = NULL;
    }

    return;
}

