#include "soundManager.h"

SoundManager::SoundManager():
	initialPlay{true}
{
	//Load files in to buffers
	laserSoundBuffer.loadFromFile("resources/laser-sound.wav");
	spiderSoundBuffer.loadFromFile("resources/spider-sound.wav");
	fleaSoundBuffer.loadFromFile("resources/flea-drop.wav");
	scorpionSoundBuffer.loadFromFile("resources/scorpion-sound.wav");
	backGroundSoundBuffer.loadFromFile("resources/background.wav");
	enemyDeathSoundBuffer.loadFromFile("resources/enemy-death.wav");
	bombDetonationSoundBuffer.loadFromFile("resources/bomb-detonation.wav");
	spiderMunchSoundBuffer.loadFromFile("resources/spider-munch.wav");
	playerDeathSoundBuffer.loadFromFile("resources/player-death.wav");
	mendMushroomSoundBuffer.loadFromFile("resources/mend-mushroom.wav");
	scoreResetSoundBuffer.loadFromFile("resources/score_reset.wav");

	//Load buffers into actual sounds
	laserSound.setBuffer(laserSoundBuffer);
	laserSound.setRelativeToListener(true);

	spiderSound.setBuffer(spiderSoundBuffer);
	spiderSound.setRelativeToListener(true);

	fleaSound.setBuffer(fleaSoundBuffer);
	fleaSound.setRelativeToListener(true);

	scorpionSound.setBuffer(scorpionSoundBuffer);
	scorpionSound.setRelativeToListener(true);

	backGroundSound.setBuffer(backGroundSoundBuffer);
	backGroundSound.setRelativeToListener(true);

	enemyDeathSound.setBuffer(enemyDeathSoundBuffer);
	enemyDeathSound.setRelativeToListener(true);

	bombDetonationSound.setBuffer(bombDetonationSoundBuffer);
	bombDetonationSound.setRelativeToListener(true);

	spiderMunchSound.setBuffer(spiderMunchSoundBuffer);
	spiderMunchSound.setRelativeToListener(true);

	playerDeathSound.setBuffer(playerDeathSoundBuffer);
	playerDeathSound.setRelativeToListener(true);

	mendMushroomSound.setBuffer(mendMushroomSoundBuffer);
	mendMushroomSound.setRelativeToListener(true);

	scoreResetSound.setBuffer(scoreResetSoundBuffer);
	scoreResetSound.setRelativeToListener(true);
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

void SoundManager::playFleaSound()
{
	fleaSound.play();
}

void SoundManager::playScorpionSound()
{
	if (scorpionSound.getStatus() == sf::Sound::Stopped)
		scorpionSound.play();
}

void SoundManager::playBackGroundSound()
{
	if (backGroundSound.getStatus() == sf::Sound::Stopped)
		backGroundSound.play();
}

void SoundManager::playEnemyDeathSound()
{
	enemyDeathSound.play();
}

void SoundManager::playBombDetonationSound()
{
	bombDetonationSound.play();
}

void SoundManager::playSpiderMunchSound()
{
	spiderMunchSound.play();
}

void SoundManager::playPlayerDeathSound()
{
	playerDeathSound.play();
}

void SoundManager::playMendMushroomSound()
{
	mendMushroomSound.play();
}

void SoundManager::playScoreResetSound()
{
	scorpionSound.stop();
	backGroundSound.stop();
	spiderSound.stop();

	if (initialPlay)
	{
		scoreResetSound.play();
		initialPlay = false;
	}

	if (scoreResetSound.getStatus() == sf::Sound::Stopped)
		scoreResetSound.play();
}