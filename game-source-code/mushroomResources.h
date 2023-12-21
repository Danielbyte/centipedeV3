#ifndef MUSHROOMRESOURCES_H
#define MUSHROOMRESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MushroomResources
{
public:
	MushroomResources();
	MushroomResources(float xPos, float yPos);
	void update_sprite(bool isPoisoned, int mushroomHealth);
	sf::Sprite get_sprite();

private:
	void load_resources();

	sf::Sprite mushroom_s;

	//normal mushroom textures
	sf::Texture mush1_t, mush2_t, mush3_t, mush4_t;

	//Poisoned mushroom textures
	sf::Texture pmush1_t, pmush2_t, pmush3_t, pmush4_t;
};
#endif
