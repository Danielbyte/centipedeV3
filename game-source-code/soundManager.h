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
    void playBackGroundSound();
    void playEnemyDeathSound();

private:
    sf::SoundBuffer laserSoundBuffer;
    sf::SoundBuffer spiderSoundBuffer;
    sf::SoundBuffer fleaSoundBuffer;
    sf::SoundBuffer scorpionSoundBuffer;
    sf::SoundBuffer backGroundSoundBuffer;
    sf::SoundBuffer enemyDeathSoundBuffer;

    sf::Sound laserSound;
    sf::Sound spiderSound;
    sf::Sound fleaSound;
    sf::Sound scorpionSound;
    sf::Sound backGroundSound;
    sf::Sound enemyDeathSound;

};
#endif // SOUNDMANAGER_H
