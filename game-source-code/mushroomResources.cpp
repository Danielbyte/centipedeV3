#include "mushroomResources.h"

MushroomResources::MushroomResources(){}

MushroomResources::MushroomResources(float xPos, float yPos)
{
	mushroom_s.setOrigin(sf::Vector2f(0.f, 0.f));
	mushroom_s.setPosition(xPos, yPos);
	mushroom_s.setScale(1, 1);
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

void MushroomResources::update_sprite(bool isPoisoned, int mushroomHealth)
{

	if (isPoisoned)
	{
		switch (mushroomHealth)
		{
		case 1:
			mushroom_s.setTexture(pmush1_t);
			break;
		case 2:
			mushroom_s.setTexture(pmush2_t);
			break;
		case 3:
			mushroom_s.setTexture(pmush3_t);
			break;
		default:
			mushroom_s.setTexture(pmush4_t);
			break;
		}
		return;
	}

	switch (mushroomHealth)
	{
	case 1:
		mushroom_s.setTexture(mush1_t);
		break;
	case 2:
		mushroom_s.setTexture(mush2_t);
		break;
	case 3:
		mushroom_s.setTexture(mush3_t);
		break;
	default:
		mushroom_s.setTexture(mush4_t);
		break;
	}
}

sf::Sprite MushroomResources::get_sprite()
{
	return mushroom_s;
}
