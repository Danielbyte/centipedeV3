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
    player_image{"resources/player.png"}
{}

void Player::setPlayer_movement(Direction dir, bool isPressed, Sprite& player_sprite)
{
    //get the player speed
    player_speed = getPlayer_speed();
    Clock dt_clock;
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

