#include "soundManager.h"

SoundManager::SoundManager()
{
	//Load files in to buffers
	laserSoundBuffer.loadFromFile("resources/laser-sound.wav");

	//Load buffers into actual sounds
	laserSound.setBuffer(laserSoundBuffer);
	laserSound.setRelativeToListener(true);
}

void SoundManager::playLaserSound()
{
	laserSound.play();
}