#ifndef PLAYER_H
#define PLAYER_H
#include "GameDataType.h"
#include "SfmlDataType.h"
#include "mushroomFieldController.h"
//#include "ScreenManager.h"
//#include "Logic.h"

class Player
{
public:
    Player();
    void setPlayer_movement(Direction, bool, Sprite&);
    void setPlayer_movement(Direction, Sprite&, sf::Time);
    bool getPlayer_movement(Direction) const;

    void set_Xposition(float);
    void set_Yposition(float);

    float get_Yposition() const;
    float get_Xposition() const;

    void setPlayer_speed(float);
    float getPlayer_speed() const;

    //decrement player lives if it collides with centipede
    void decrement_lives();
    //get live remaining
    int getPlayer_lives() const;

    // update state of player
    void setPlayer_state(bool var);
    bool getPlayer_state() const;

private:
    //mark player movement
    bool playerMovingUp;
    bool playerMovingDown;
    bool playerMovingLeft;
    bool playerMovingRight;

    const float player_size;
    const float player_center;
    float player_speed;
    float y_position;
    float x_position;

    //set the status of player (dead or alive)
    bool isPlayerAlive;

    //player lives
    int player_lives;

    std::string player_image;

};
#endif // PLAYER_H
