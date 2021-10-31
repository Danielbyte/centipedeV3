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

}

vector2f Scorpion::create_scorpion()
{
    control++;
    //set the position of scorpion
    pos.x = (30.f)*offset; // scorpion will move from right to left

    srand(time(0));
    //int min = 5;
    //int max = 10;
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

    return pos;
}

bool Scorpion::getIfCanSpawn_scorpion() const
{
    return canCreate_scorpion;
}

void Scorpion::setIfCanSpawn_scorpion(bool var)
{
    canCreate_scorpion = var;
}

void Scorpion::update(shared_ptr<Sprite>& scorpion_sprite,float _time)
{
    //only updating when scorpion has been created
    if (_time > spawnScorpion_rate)
    {
        isOffScreen = false;
        if (counter == 0)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
            scorpion_sprite -> setTexture(scorpion_texture);
        }

        if (counter == 5)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion2.png")) throw CouldNotLoadPicture{};
            scorpion_sprite -> setTexture(scorpion_texture);
        }

        if(counter == 10)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion3.png")) throw CouldNotLoadPicture{};
            scorpion_sprite -> setTexture(scorpion_texture);
        }

        if(counter == 15)
        {
            if(!scorpion_texture.loadFromFile("resources/scorpion4.png")) throw CouldNotLoadPicture{};
            scorpion_sprite -> setTexture(scorpion_texture);
            counter = 0;
        }

        pos.x -= scorpion_speed;
        scorpion_sprite -> setPosition(pos);
        scorpion_sprite -> setOrigin(vector2f(0.f,0.f));
        counter++;
    }

    if (pos.x <= -offset)
    {
        scorpion_sprite.reset(new Sprite);
        isOffScreen = true;
    }

}

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


