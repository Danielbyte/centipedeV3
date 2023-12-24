#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "gameResources.h"

class SoundManager
{
public:
    SoundManager();
    void playLaserSound();
    void playSpiderSound();
    void playFleaSound();

private:
    sf::SoundBuffer laserSoundBuffer;
    sf::SoundBuffer spiderSoundBuffer;
    sf::SoundBuffer fleaSoundBuffer;

    sf::Sound laserSound;
    sf::Sound spiderSound;
    sf::Sound fleaSound;

};
#endif // SOUNDMANAGER_H
