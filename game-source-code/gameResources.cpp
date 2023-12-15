#include "gameResources.h"

GameResources::GameResources()
{
	mushroom_s.setOrigin(sf::Vector2f(0.f, 0.f));
	centipedeHead_s.setOrigin(sf::Vector2f(centipedeBody_size/2.0f, centipedeBody_size/2.0f));
	centipedeBody_s.setOrigin(sf::Vector2f(centipedeBody_size/2.0f, centipedeBody_size/2.0f));
	mushroom_s.setScale(1, 1);
	load_resources();
}

void GameResources::load_resources()
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

	//centipede resources
	head1_t.loadFromFile("resources/head1.png");
	head2_t.loadFromFile("resources/head2.png");
	head3_t.loadFromFile("resources/head3.png");
	head4_t.loadFromFile("resources/head4.png");
	head5_t.loadFromFile("resources/head5.png");
	head6_t.loadFromFile("resources/head6.png");
	head7_t.loadFromFile("resources/head7.png");
	head8_t.loadFromFile("resources/head8.png");

	body1_t.loadFromFile("resources/body1.png");
	body2_t.loadFromFile("resources/body2.png");
	body3_t.loadFromFile("resources/body3.png");
	body4_t.loadFromFile("resources/body4.png");
	body5_t.loadFromFile("resources/body5.png");
	body6_t.loadFromFile("resources/body6.png");
	body7_t.loadFromFile("resources/body7.png");
	body8_t.loadFromFile("resources/body8.png");
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

sf::Sprite GameResources::getSegmentSprite(sf::Vector2f segmentPosition, int counter, bool isHead, float rotation)
{
	if (isHead)
	{
		centipedeHead_s.setPosition(segmentPosition);
		centipedeHead_s.rotate(rotation);
		switch (counter)
		{
		case 0:
		case 1:
		case 2:
			centipedeHead_s.setTexture(head1_t);
			return centipedeHead_s;
		case 3:
		case 4:
		case 5:
			centipedeHead_s.setTexture(head2_t);
			return centipedeHead_s;
		case 6:
		case 7:
		case 8:
			centipedeHead_s.setTexture(head3_t);
			return centipedeHead_s;
		case 9:
		case 10:
		case 11:
			centipedeHead_s.setTexture(head4_t);
			return centipedeHead_s;
		case 12:
		case 13:
		case 14:
			centipedeHead_s.setTexture(head5_t);
			return centipedeHead_s;
		case 15:
		case 16:
		case 17:
			centipedeHead_s.setTexture(head6_t);
			return centipedeHead_s;
		case 18:
		case 19:
		case 20:
			centipedeHead_s.setTexture(head7_t);
			return centipedeHead_s;
		case 21:
			centipedeHead_s.setTexture(head8_t);
			return centipedeHead_s;
		default:
			//return centipedeHead_s;
			break;
		}
	}

	centipedeBody_s.setPosition(segmentPosition);
	centipedeBody_s.rotate(rotation);
	switch (counter)
	{
	case 0:
	case 1:
	case 2:
		centipedeBody_s.setTexture(body1_t);
		return centipedeBody_s;
	case 3:
	case 4:
	case 5:
		centipedeBody_s.setTexture(body2_t);
		return centipedeBody_s;
	case 6:
	case 7:
	case 8:
		centipedeBody_s.setTexture(body3_t);
		return centipedeBody_s;
	case 9:
	case 10:
	case 11:
		centipedeBody_s.setTexture(body4_t);
		return centipedeBody_s;
	case 12:
	case 13:
	case 14:
		centipedeBody_s.setTexture(body5_t);
		return centipedeBody_s;
	case 15:
	case 16:
	case 17:
		centipedeBody_s.setTexture(body6_t);
		return centipedeBody_s;
	case 18:
	case 19:
	case 20:
		centipedeBody_s.setTexture(body7_t);
		return centipedeBody_s;
	case 21:
		centipedeBody_s.setTexture(body8_t);
		return centipedeBody_s;
	default:
		//return centipedeBody_s;
		break;
	}
}
