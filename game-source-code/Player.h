#ifndef PLAYER_H
#define PLAYER_H
#include "GameDataType.h"
#include "gameResources.h"
#include "StopWatch.h"

class Player
{
public:
    Player();
    void setPlayer_movement(Direction, bool, bool inDeathAnimation, sf::Sprite&);
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
    void updatePlayerTexture(bool& isInDeathAnimaion, sf::Sprite& player_sprite);
    void restartAnimationWatch();

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
    shared_ptr<StopWatch>animation_watch = std::make_shared<StopWatch>();

    void load_resorces();
    sf::Texture death1_t, death2_t, death3_t, death4_t, death5_t, death6_t, death7_t, death8_t, death9_t;
    sf::Texture death10_t, death11_t, death12_t, death13_t, death14_t, player;
    float animation_period;

};
#endif // PLAYER_H
