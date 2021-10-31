#include "Scorpion.h"
#include "Logic.h"

Scorpion::Scorpion():
    scorpion_speed{2},
    spawnScorpion_rate{4}, //spawn scorpion after 10 seconds
    canCreate_scorpion{false},
    isOffScreen{true}, //scorpion initially off screen when created
    counter{0},
    control{0}
{
    pos.x = (30.f)*offset;
    pos.y = 160.f;
}

/*vector2f Scorpion::create_scorpion()
{
    //set the position of scorpion
    pos.x = (30.f)*offset; // scorpion will move from right to left

    srand(time(0));
    // randomly generate row position bearing in mind that it should not
    // be in player area.
    if (control == 1)
    {
        pos.y = 160.f;
    }
    if (control == 2)
    {
        pos.y = 176.f;

    }

    if (control == 3)
    {
        pos.y = 208.f;
        control = 0;
    }
}*/

bool Scorpion::getIfCanSpawn_scorpion() const
{
    return canCreate_scorpion;
}

void Scorpion::setIfCanSpawn_scorpion(bool var)
{
    canCreate_scorpion = var;
}

void Scorpion::reset_counter()
{
    counter = 0;
}

void Scorpion::increment_counter()
{
    counter++;
}

int Scorpion::get_counter() const
{
    return counter;
}

/*void Scorpion::update(vector<shared_ptr<Sprite>>& scorpion_sprite,float _time)
{
    //only updating when scorpion has been created
    auto scorpion_sprite_iter = scorpion_sprite.begin();
    if (_time > spawnScorpion_rate)
    {
        isOffScreen = false;
        if (counter == 0)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
            (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
        }

        if (counter == 5)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion2.png")) throw CouldNotLoadPicture{};
            (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
        }

        if(counter == 10)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion3.png")) throw CouldNotLoadPicture{};
            (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
        }

        if(counter == 15)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion4.png")) throw CouldNotLoadPicture{};
            (*scorpion_sprite_iter) -> setTexture(scorpion_texture);
            counter = 0;
        }

        pos.x -= scorpion_speed;
        (*scorpion_sprite_iter) -> setPosition(pos);
        (*scorpion_sprite_iter) -> setOrigin(vector2f(0.f,0.f));
        counter++;
    }

    if (pos.x <= -offset)
    {
        scorpion_sprite.erase(scorpion_sprite_iter);
        std::cout<< "Deleted scorpion!" << std::endl;
        isOffScreen = true;
        return;
    }

}*/

int Scorpion::getScorpion_spawnRate() const
{
    return spawnScorpion_rate;
}

vector2f Scorpion::getScorpion_position() const
{
    return pos;
}

bool Scorpion::getIfOffScreen() const
{
    return isOffScreen;
}


