#ifndef SPIDERCONTROLLER_H
#define SPIDERCONTROLLER_H
#include "Spider.h"
#include "GameDataType.h"
#include "StopWatch.h"
#include <ctime>
#include <queue>

class SpiderController
{
public:
    SpiderController();
    ~SpiderController();
    void update_spider(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<Spider>>&);
private:

    void move_up();
    void move_down();
    void move_diagonal_up();
    void move_diagonal_down();
    int selection;

    //queue to store the movement logic of spider(instructions/orders)
    std::queue<sf::Vector2f> movement_logic;
    sf::Vector2f logic_position;

    float spider_speed;
    //initial left position of spider(if spawned left)
    float left_pos;
    //initial right position of spider (if spawned right)
    float right_pos;
    //height at which spider spawns
    float spawn_height;
    //the highest point which spider can travel
    int max_pos;
    //lowest point which spider can travel
    int min_pos;
    //minimum movement instruction given to spider per order
    int min_instruction;
    //maximum instruction given to spider per orde
    int max_instruction;

    void initialize_movement(shared_ptr<Spider>&);

    //if spider is moving left or right
    bool isToRight;

    //updates if centipede moves left or right
    int direction_marker;
    Direction direction;

    void delete_queue();
    void Animate_spider(shared_ptr<sf::Sprite>&, shared_ptr<Spider>&);
    void load_resources();
    sf::Texture spider1_t, spider2_t, spider3_t, spider4_t, spider5_t, spider6_t, spider7_t, spider8_t;
    sf::Texture death1_t, death2_t, death3_t, death4_t, death5_t, death6_t;

    float deathFramePeriod;
};
#endif // SPIDERCONTROLLER_H
