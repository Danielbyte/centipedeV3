#ifndef LOGIC_H
#define LOGIC_H

#include "Scorpion.h"
#include "GameDataType.h"
#include "Player.h"
#include "LaserShots.h"
#include "GameDataType.h"
#include "Collision.h"
#include "Centipede.h"
#include "StopWatch.h"
#include "centipedeAnimation.h"
#include "Spider.h"
#include "SpiderController.h"
#include "DDTBombs.h"
#include "DDTBombsController.h"
#include "ScorpionController.h"
#include "CentipedeController.h"
#include "Flea.h"
#include "FleaController.h"
#include "mushroomResources.h"

class Logic
{
public:
    Logic();
    ~Logic();
    Player player_object;
    void update_player(sf::Sprite&);
    shared_ptr<LaserShots>LaserShots_object;
    void updateLaserShots(vector<shared_ptr<sf::Sprite>>&);
    void create_centipede(bool, int, vector<shared_ptr<sf::Sprite>>&);
    vector<shared_ptr<Centipede>>centipede_objectVector;
    vector<shared_ptr<Centipede>>shot_centipede_segments;
    void update_centipede(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>& mushField);
    sf::Texture bomb_texture;

    void collisionBetween_mushAndPlayer(sf::Sprite&, vector<shared_ptr<MushroomField>>& mushField);
    sf::Texture centipede_texture;
    sf::Texture centipedeBody_texture;

    void collisionBetweenBulletsAndObjects(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&,
        vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    void create_bullet(vector<shared_ptr<sf::Sprite>>&);

    int getKilled_segments() const;

    //scorpion watches
    vector<shared_ptr<Scorpion>>scorpion_object_vector;
    sf::Vector2f create_scorpion();
    StopWatch scorpion_watch;
    StopWatch scorpion_watch2;

    //set and get if scorpion can be spawned
    bool canSpawn_scorpion();
    void update_scorpion(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    //spider watches
    StopWatch spider_watch;
    //update spider
    void update_spider(vector <shared_ptr<sf::Sprite>>&);
    //vector of shared pointer to spider
    vector<shared_ptr<Spider>>spider_object_vector;
    bool getIfCanSpawnSpider();

    sf::Vector2f create_spider();

    //collision between spider and mushroom
    //isTest to denote if is game play or test coverage
    void collision_between_mush_and_spider(bool isTest,vector<shared_ptr<MushroomField>>& mushField,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites); 

    //collision between player and Spider
    void collision_between_player_and_spider(sf::Sprite&);

    //collision between bullet and spider
    void collision_btwn_bullet_and_spider(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&);

    //collision between bomb and bullet
    void collision_between_bullet_and_bomb(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&,
                                           vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&, sf::Sprite&,
                                           vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>&,
                                           vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    //collisions between bullet and flea
    void collision_between_bullet_and_flea(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&);

    //collision between player and flea
    void collision_between_player_and_flea(sf::Sprite&);

    void collision_between_bullet_and_scorpion(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&);
    void collision_between_centipede_and_player(sf::Sprite&);

    void collision_between_centipede_and_bullet(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<sf::Sprite>>&,
                                                vector<shared_ptr<MushroomField>>&,
                                                vector<shared_ptr<sf::Sprite>>& mushroom_sprites,
                                                vector<shared_ptr<sf::Sprite>>& shot_segments);

    void delete_segment_and_spawn_mushroom(vector<shared_ptr<sf::Sprite>>&, 
        vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    //DDT object vector
    vector <shared_ptr<DDTBombs>>vector_of_bomb_objects;
    bool getIfCanSpawnBomb();

    sf::Vector2f create_bomb();

    bool getIfCanSpawnFlea(vector<shared_ptr<MushroomField>>& mushField);
    sf::Vector2f create_flea();
    void update_flea(vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<sf::Sprite>>& mushroom_sprites);
    vector<shared_ptr<Flea>>flea_object;

    int get_score() const;

    //For Test Purposes of spider collision with mush
    float get_lunch_time();
    void set_lunch(float);
    void setSpiderToHungry(bool);

    void create_mushrooms(vector<shared_ptr<MushroomField>>& mushroom_obejects,
        vector<std::shared_ptr<sf::Sprite>>& mushroom_sprites);

    void update_shot_centipede_segments(vector<shared_ptr<sf::Sprite>>& centipede_sprites,
        vector<shared_ptr<MushroomField>>& mushroom_field);

private:
    //dummy variables for tests(to alter spider's lunch time);
    float dummy;
    bool spiderIsHungry;

    //Object for the Spider logic and update
    CentipedeController centipede_controller;
    SpiderController spider_control;
    Spider spider;
    centipedeAnimation animation;
    Collision collision;
    FleaController flea_control;

    //Scorpion
    Scorpion scorpion;
    ScorpionController control_scorpion;

    DDTBombsController bomb_controller;

    int playerArea_upBound;
    int centipedeAnimationCounter;

    //variables for centipede creation
    bool isHead;
    //Notify if hit by bullet to control how centipede detects collissions
    bool isHit;
    int bodySegmentsTo_spawn;
    //variables to see if centipede moving up or down
    bool ismovingUp;
    bool ismovingDown;
    // variables to command centipede to move up or down
    bool moveDown;
    bool moveUp;
    int update_counter;

    //variables specific to body piece
    int body_counter;
    int Test_counter;

    // spawn a body segment behind
    void spawn_behind(vector<shared_ptr<sf::Sprite>>&);

    //logic for the centipede
    sf::Vector2f pos;

    sf::Texture bullet_texture;

    bool MushCollidedWith_bullet;

    //keep track of shot centipede segments
    int shotCent_segments;
    bool created_scorpion;

    //a flag for spawning a spider
    bool canSpawnSpider;

    //timer to set when spider gets hungry
    StopWatch lunch_time;


    //DDT bombs
    //check if bomb controller is willing to create a bomb
    //after some certain time
    StopWatch bomb_check;

    int score;
    Direction dir;
    Direction dir1;
    
    shared_ptr<MushroomResources> mushroom_resource = std::make_shared<MushroomResources>();
    shared_ptr<SoundManager> sound_manager = std::make_shared<SoundManager>();
};

#endif // LOGIC_H
