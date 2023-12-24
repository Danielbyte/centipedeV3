#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "gameResources.h"

class SoundManager
{
public:
    SoundManager();
    void playLaserSound();

private:
    sf::SoundBuffer laserSoundBuffer;
    sf::Sound laserSound;

};
#endif // SOUNDMANAGER_H
