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
    void playBombDetonationSound();
    void playSpiderMunchSound();

private:
    sf::SoundBuffer laserSoundBuffer;
    sf::SoundBuffer spiderSoundBuffer;
    sf::SoundBuffer fleaSoundBuffer;
    sf::SoundBuffer scorpionSoundBuffer;
    sf::SoundBuffer backGroundSoundBuffer;
    sf::SoundBuffer enemyDeathSoundBuffer;
    sf::SoundBuffer bombDetonationSoundBuffer;
    sf::SoundBuffer spiderMunchSoundBuffer;

    sf::Sound laserSound;
    sf::Sound spiderSound;
    sf::Sound fleaSound;
    sf::Sound scorpionSound;
    sf::Sound backGroundSound;
    sf::Sound enemyDeathSound;
    sf::Sound bombDetonationSound;
    sf::Sound spiderMunchSound;
};
#endif // SOUNDMANAGER_H
