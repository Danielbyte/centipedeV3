#include "gameResources.h"

GameResources::GameResources()
{
	mushroom_s.setOrigin(sf::Vector2f(0.f, 0.f));
	mushroom_s.setScale(1, 1);
	load_resources();
}

void GameResources::load_resources()
{
	mush4_t.loadFromFile("resources/mushroom.png", sf::IntRect(0, 0, 16, 16));
	mush3_t.loadFromFile("resources/mush1.png");
	mush2_t.loadFromFile("resources/mush2.png");
	mush1_t.loadFromFile("resources/mush3.png");

	pmush1_t.loadFromFile("resources/pmush4.png");
	pmush2_t.loadFromFile("resources/pmush3.png");
	pmush3_t.loadFromFile("resources/pmush2.png");
	pmush4_t.loadFromFile("resources/pmush1.png");
}

sf::Sprite GameResources::getMushroomSprite(sf::Vector2f mushroomPosition, bool isPoisoned, int mushroomHealth)
{
	mushroom_s.setPosition(mushroomPosition);

	if (isPoisoned)
	{
		switch (mushroomHealth)
		{
		case 1:
			mushroom_s.setTexture(pmush1_t);
			return mushroom_s;
		case 2:
			mushroom_s.setTexture(pmush2_t);
			return mushroom_s;
		case 3:
			mushroom_s.setTexture(pmush3_t);
			return mushroom_s;
		default:
			mushroom_s.setTexture(pmush4_t);
			return mushroom_s;
			break;
		}
	}

	switch (mushroomHealth)
	{
	case 1:
		mushroom_s.setTexture(mush1_t);
		return mushroom_s;
	case 2:
		mushroom_s.setTexture(mush2_t);
		return mushroom_s;
	case 3:
		mushroom_s.setTexture(mush3_t);
		return mushroom_s;
	default:
		mushroom_s.setTexture(mush4_t);
		return mushroom_s;
		break;
	}
}
