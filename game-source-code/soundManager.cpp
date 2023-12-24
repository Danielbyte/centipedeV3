#include "soundManager.h"

SoundManager::SoundManager()
{
	//Load files in to buffers
	laserSoundBuffer.loadFromFile("resources/laser-sound.wav");
	spiderSoundBuffer.loadFromFile("resources/spider-sound.wav");

	//Load buffers into actual sounds
	laserSound.setBuffer(laserSoundBuffer);
	laserSound.setRelativeToListener(true);

	spiderSound.setBuffer(spiderSoundBuffer);
	spiderSound.setRelativeToListener(true);
}

void SoundManager::playLaserSound()
{
	laserSound.play();
}

void SoundManager::playSpiderSound()
{
	if (spiderSound.getStatus() == sf::Sound::Stopped)
		spiderSound.play();
}