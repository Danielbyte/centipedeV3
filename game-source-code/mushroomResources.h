#ifndef MUSHROOMRESOURCES_H
#define MUSHROOMRESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MushroomResources
{
public:
	MushroomResources();
	void update_sprite(bool isPoisoned, int mushroomHealth, std::shared_ptr<sf::Sprite>& mushroom_sprite);

private:
	void load_resources();

	//normal mushroom textures
	sf::Texture mush1_t, mush2_t, mush3_t, mush4_t;

	//Poisoned mushroom textures
	sf::Texture pmush1_t, pmush2_t, pmush3_t, pmush4_t;
};
#endif
