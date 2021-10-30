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
    std::cout<< "start" << std::endl;
    auto row = (rand() % 20) + 6;
    auto col =(rand() % 20) + 6;
    /* if (!mushField ->isMushroom(row, col))
     {
         return;
     }



     //do not generate on position where there is a mushroom
     std::cout << "Came!" << std::endl;
     bool isGenerated = false;
     while (mushField ->isMushroom(row, col))
     {
         std::cout << "Caame!" << std::endl;
         auto row = (rand() % 20) + 6;
         auto col =(rand() % 20) + 6;
     }*/

    pos.x = col*offset;
    pos.y = row*offset;

    std::cout << "ended" << std::endl;
}

vector2f DDTBombsController::getGeneratedPosition() const
{
    return pos;
}

void DDTBombsController::Explosion(vector<shared_ptr<DDTBombs>>& bombObj, vector<shared_ptr<Sprite>>& bombSprite,
                                   shared_ptr<MushroomFieldController>& mushField)
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

                //check collision between explosion and mushroom
                explosion_and_mush((*bombSprite_iter), mushField);

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
            }

            if (counter == 30)
            {

                bombObj.erase(bomb_iter);
                bombSprite.erase(bombSprite_iter);
                return;
            }

            (*bomb_iter) -> increment_counter();
            //std::cout << "counter: "<<counter << std::endl;

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
                auto explosion_width = bomb_sprite -> getGlobalBounds().width;
                auto explosion_height = bomb_sprite -> getGlobalBounds().height;
                mushPos.x = col*offset;
                mushPos.y = row*offset;
                auto isCollided = collision.collision_detect(mushPos, mushWidth,mushHeight,explosion_pos,explosion_width,explosion_height);

                if(isCollided)
                {
                    mushField -> mushArray[row][col] = NULL;
                }
            }
        }
    }
}

