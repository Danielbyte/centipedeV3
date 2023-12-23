#include "mushroomResources.h"

MushroomResources::MushroomResources()
{
	load_resources();
}

void MushroomResources::load_resources()
{
	//Mushroom resources
	mush4_t.loadFromFile("resources/mushroom.png", sf::IntRect(0, 0, 16, 16));
	mush3_t.loadFromFile("resources/mush1.png");
	mush2_t.loadFromFile("resources/mush2.png");
	mush1_t.loadFromFile("resources/mush3.png");

	pmush1_t.loadFromFile("resources/pmush4.png");
	pmush2_t.loadFromFile("resources/pmush3.png");
	pmush3_t.loadFromFile("resources/pmush2.png");
	pmush4_t.loadFromFile("resources/pmush1.png");
}

void MushroomResources::update_sprite(bool isPoisoned, int mushroomHealth, std::shared_ptr<sf::Sprite>& mushroom_sprite)
{

	if (isPoisoned)
	{
		switch (mushroomHealth)
		{
		case 1:
			mushroom_sprite->setTexture(pmush1_t);
			break;
		case 2:
			mushroom_sprite->setTexture(pmush2_t);
			break;
		case 3:
			mushroom_sprite->setTexture(pmush3_t);
			break;
		case 4:
			mushroom_sprite->setTexture(pmush4_t);
			break;
		default:
			break;
		}
		return;
	}

	switch (mushroomHealth)
	{
	case 1:
		mushroom_sprite->setTexture(mush1_t);
		break;
	case 2:
		mushroom_sprite->setTexture(mush2_t);
		break;
	case 3:
		mushroom_sprite->setTexture(mush3_t);
		break;
	case 4:
		mushroom_sprite->setTexture(mush4_t);
		break;
	default:
		break;
	}
}
