#include "gameResources.h"

GameResources::GameResources()
{
	centipedeHead_s.setOrigin(sf::Vector2f(centipedeBody_size/2.0f, centipedeBody_size/2.0f));
	centipedeBody_s.setOrigin(sf::Vector2f(centipedeBody_size/2.0f, centipedeBody_size/2.0f));	
	load_resources();
}

void GameResources::load_resources()
{
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

void GameResources::getSegmentTexture(int counter, bool isHead, shared_ptr<sf::Sprite>& segment_sprite)
{
	if (isHead)
	{
		switch (counter)
		{
		case 0:
		case 1:
		case 2:
			segment_sprite->setTexture(head1_t);
			break;
		case 3:
		case 4:
		case 5:
			segment_sprite->setTexture(head2_t);
			break;
		case 6:
		case 7:
		case 8:
			segment_sprite->setTexture(head3_t);
			break;
		case 9:
		case 10:
		case 11:
			segment_sprite->setTexture(head4_t);
			break;
		case 12:
		case 13:
		case 14:
			segment_sprite->setTexture(head5_t);
			break;
		case 15:
		case 16:
		case 17:
			segment_sprite->setTexture(head6_t);
			break;
		case 18:
		case 19:
		case 20:
			segment_sprite->setTexture(head7_t);
			break;
		case 21:
			segment_sprite->setTexture(head8_t);
			break;
		default:
			break;
		}

		return;
	}

	switch (counter)
	{
	case 0:
	case 1:
	case 2:
		segment_sprite->setTexture(body1_t);
		break;
	case 3:
	case 4:
	case 5:
		segment_sprite->setTexture(body2_t);
		break;
	case 6:
	case 7:
	case 8:
		segment_sprite->setTexture(body3_t);
		break;
	case 9:
	case 10:
	case 11:
		segment_sprite->setTexture(body4_t);
		break;
	case 12:
	case 13:
	case 14:
		segment_sprite->setTexture(body5_t);
		break;
	case 15:
	case 16:
	case 17:
		segment_sprite->setTexture(body6_t);
		break;
	case 18:
	case 19:
	case 20:
		segment_sprite->setTexture(body7_t);
		break;
	case 21:
		segment_sprite->setTexture(body8_t);
		break;
	default:
		break;
	}
}
