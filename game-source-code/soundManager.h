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
    void playPlayerDeathSound();
    void playMendMushroomSound();
    void playScoreResetSound();

private:
    sf::SoundBuffer laserSoundBuffer;
    sf::SoundBuffer spiderSoundBuffer;
    sf::SoundBuffer fleaSoundBuffer;
    sf::SoundBuffer scorpionSoundBuffer;
    sf::SoundBuffer backGroundSoundBuffer;
    sf::SoundBuffer enemyDeathSoundBuffer;
    sf::SoundBuffer bombDetonationSoundBuffer;
    sf::SoundBuffer spiderMunchSoundBuffer;
    sf::SoundBuffer playerDeathSoundBuffer;
    sf::SoundBuffer mendMushroomSoundBuffer;
    sf::SoundBuffer scoreResetSoundBuffer;

    sf::Sound laserSound;
    sf::Sound spiderSound;
    sf::Sound fleaSound;
    sf::Sound scorpionSound;
    sf::Sound backGroundSound;
    sf::Sound enemyDeathSound;
    sf::Sound bombDetonationSound;
    sf::Sound spiderMunchSound;
    sf::Sound playerDeathSound;
    sf::Sound mendMushroomSound;
    sf::Sound scoreResetSound;

    bool initialPlay;
};
#endif // SOUNDMANAGER_H
