#include "Player.h"

Player::Player():
    playerMovingUp{false},
    playerMovingDown{false},
    playerMovingLeft{false},
    playerMovingRight{false},
    player_size{16}, //pixel size of playerID
    player_center{8}, // of pplayerID
    player_speed{4},
    y_position{504},
    x_position{240}, // Initial player position at bottom center
    isPlayerAlive{true}, //player initially alive
    player_lives{3}, // player will have three lives
    player_image{"resources/player.png"},
    animation_period{0.05f}
{
    load_resorces();
}

void Player::setPlayer_movement(Direction dir, bool isPressed, bool inDeathAnimation, sf::Sprite& player_sprite)
{
    if (inDeathAnimation)
        return;

    //get the player speed
    player_speed = getPlayer_speed();
    sf::Clock dt_clock;
    auto dt = dt_clock.restart().asSeconds();

    switch(dir)
    {
    case Direction::Up:
        y_position -= player_speed;
        playerMovingUp = isPressed;
        if (y_position <= 376) //limit player's movement from the bottom of screen
            y_position = 376;
        break;

    case Direction::Down:
        y_position += player_speed;
        playerMovingDown = isPressed;
        if(y_position >= 504) //bottom boundary of player
            y_position = 504;
        break;

    case Direction::Left:
        x_position -= player_speed;
        playerMovingLeft = isPressed;
        if (x_position <= 8) //left boundary of player
            x_position = 8;
        break;

    case Direction::Right:
        x_position += player_speed;
        playerMovingRight = isPressed;
        if (x_position >= 472) //right boundary of player
            x_position = 472;
        break;

    default:
        ;
    }
}

bool Player::getPlayer_movement(Direction dir) const
{
    switch(dir)
    {
    case Direction::Up:
        return playerMovingUp;
        break;

    case Direction::Down:
        return playerMovingDown;
        break;

    case Direction::Left:
        return playerMovingLeft;
        break;

    case Direction::Right:
        return playerMovingRight;
        break;

    default:
        ;
    }
    return false; //control does not reach here, can return whatever value
}

void Player::set_Xposition(float x_pos)
{
    x_position=x_pos;
}
void Player::set_Yposition(float y_pos)
{
    y_position=y_pos;
}

float Player::get_Yposition() const
{
    return y_position;
}

float Player::get_Xposition () const
{
    return x_position;
}

void Player::setPlayer_speed(float speed)
{
    player_speed = speed;
}

float Player::getPlayer_speed() const
{
    return player_speed;
}

void Player::decrement_lives()
{
    --player_lives;
}

int Player::getPlayer_lives() const
{
    return player_lives;
}

void Player::setPlayer_state(bool var)
{
    isPlayerAlive = var;
}

bool Player::getPlayer_state() const
{
    return isPlayerAlive;
}

void Player::updatePlayerTexture(bool& isInDeathAnimation, bool& canMendMushrooms, sf::Sprite& player_sprite,
    shared_ptr<StopWatch>& mend_mushroom_watch)
{
    if (isInDeathAnimation)
    {
        auto time = animation_watch->getTimeElapsed();
        if (time >= 0.0f && time <= animation_period)
        {
            player_sprite.setTexture(death1_t);
            return;
        }
        if (time > animation_period && time <= 2 * animation_period)
        {
            player_sprite.setTexture(death2_t);
            return;
        }
        if (time > 2 * animation_period && time <= 3 * animation_period)
        {
            player_sprite.setTexture(death3_t);
            return;
        }
        if (time > 3 * animation_period && time <= 4 * animation_period)
        {
            player_sprite.setTexture(death4_t);
            return;
        }
        if (time > 4 * animation_period && time <= 5 * animation_period)
        {
            player_sprite.setTexture(death5_t);
            return;
        }
        if (time > 5 * animation_period && time <= 6 * animation_period)
        {
            player_sprite.setTexture(death6_t);
            return;
        }
        if (time > 6 * animation_period && time <= 7 * animation_period)
        {
            player_sprite.setTexture(death7_t);
            return;
        }
        if (time > 7 * animation_period && time <= 8 * animation_period)
        {
            player_sprite.setTexture(death8_t);
            return;
        }
        if (time > 8 * animation_period && time <= 9 * animation_period)
        {
            player_sprite.setTexture(death9_t);
            return;
        }
        if (time > 9 * animation_period && time <= 10 * animation_period)
        {
            player_sprite.setTexture(death10_t);
            return;
        }
        if (time > 10 * animation_period && time <= 11 * animation_period)
        {
            player_sprite.setTexture(death11_t);
            return;
        }
        if (time > 11 * animation_period && time <= 12 * animation_period)
        {
            player_sprite.setTexture(death12_t);
            return;
        }
        if (time > 12 * animation_period && time <= 13 * animation_period)
        {
            player_sprite.setTexture(death13_t);
            return;
        }
        if (time > 13 * animation_period && time <= 14 * animation_period)
        {
            player_sprite.setTexture(death14_t);
            return;
        }
        isInDeathAnimation = false;
        canMendMushrooms = true;
        mend_mushroom_watch->restart();
        return;
    }

    player_sprite.setTexture(player);
}

void Player::restartAnimationWatch()
{
    animation_watch->restart();
}

void Player::load_resorces()
{
    death1_t.loadFromFile("resources/player-death1.png");
    death2_t.loadFromFile("resources/player-death2.png");
    death3_t.loadFromFile("resources/player-death3.png");
    death4_t.loadFromFile("resources/player-death4.png");
    death5_t.loadFromFile("resources/player-death5.png");
    death6_t.loadFromFile("resources/player-death6.png");
    death7_t.loadFromFile("resources/player-death7.png");
    death8_t.loadFromFile("resources/player-death8.png");
    death9_t.loadFromFile("resources/player-death9.png");
    death10_t.loadFromFile("resources/player-death10.png");
    death11_t.loadFromFile("resources/player-death11.png");
    death12_t.loadFromFile("resources/player-death12.png");
    death13_t.loadFromFile("resources/player-death13.png");
    death14_t.loadFromFile("resources/player-death14.png");
    player.loadFromFile("resources/player.png");
}

