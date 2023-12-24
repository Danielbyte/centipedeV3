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
    void playScorpionSound();

private:
    sf::SoundBuffer laserSoundBuffer;
    sf::SoundBuffer spiderSoundBuffer;
    sf::SoundBuffer fleaSoundBuffer;
    sf::SoundBuffer scorpionSoundBuffer;

    sf::Sound laserSound;
    sf::Sound spiderSound;
    sf::Sound fleaSound;
    sf::Sound scorpionSound;

};
#endif // SOUNDMANAGER_H
