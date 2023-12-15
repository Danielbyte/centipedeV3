#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameResources
{
public:
	GameResources();
	sf::Sprite getMushroomSprite(sf::Vector2f mushroomPosition, bool isPoisoned, int mushroomHealth);

private:
	void load_resources();

	//normal mushroom sprite and textures
	sf::Texture mush1_t, mush2_t, mush3_t, mush4_t;
	sf::Sprite mushroom_s;

	//Poisoned mushroom sprites and textures
	sf::Texture pmush1_t, pmush2_t, pmush3_t, pmush4_t;
	sf::Sprite pmush1_s, pmush2_s, pmush3_s, pmush4_s;
};
#endif
