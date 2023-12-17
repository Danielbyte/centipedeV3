#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameDataType.h"

class GameResources
{
public:
	GameResources();
	sf::Sprite getMushroomSprite(sf::Vector2f mushroomPosition, bool isPoisoned, int mushroomHealth);
	void getSegmentTexture(int counter, bool isHead, shared_ptr<sf::Sprite>& segment_sprite);

private:
	void load_resources();

	sf::Sprite mushroom_s;
	sf::Sprite centipedeHead_s, centipedeBody_s;

	//normal mushroom textures
	sf::Texture mush1_t, mush2_t, mush3_t, mush4_t;

	//Poisoned mushroom textures
	sf::Texture pmush1_t, pmush2_t, pmush3_t, pmush4_t;

	//centipede head textures
	sf::Texture head1_t, head2_t, head3_t, head4_t, head5_t, head6_t, head7_t, head8_t;

	//centipede body textures
	sf::Texture body1_t, body2_t, body3_t, body4_t, body5_t, body6_t, body7_t, body8_t;
};
#endif
