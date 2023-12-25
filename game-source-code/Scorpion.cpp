#include "Scorpion.h"
#include "Logic.h"

Scorpion::Scorpion():
    scorpion_speed{2},
    spawnScorpion_rate{8}, //spawn scorpion after 5 seconds
    canCreate_scorpion{false},
    counter{0},
    control{0},
    inDeathAnimation{false},
    canDestroy{false}
{
}

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

float Scorpion::getScorpion_spawnRate() const
{
    return spawnScorpion_rate;
}

sf::Vector2f Scorpion::getScorpion_position() const
{
    return pos;
}

bool Scorpion::getIfOffScreen() const
{
    return isOffScreen;
}

float Scorpion::get_scorpion_speed() const
{
    return scorpion_speed;
}

void Scorpion::set_position(sf::Vector2f pos)
{
    this -> pos = pos;
}

void Scorpion::play_sound()
{
    sound_manager->playScorpionSound();
}

void Scorpion::startDeathAnimation()
{
    inDeathAnimation = true;
    death_animation_watch->restart();
}

void Scorpion::destroy_object()
{
    canDestroy = true;
}

bool Scorpion::CanDestroy() const
{
    return canDestroy;
}

float Scorpion::getAnimationTime() const
{
    return (death_animation_watch->getTimeElapsed());
}

bool Scorpion::isInDeathAnimation() const
{
    return inDeathAnimation;
}
