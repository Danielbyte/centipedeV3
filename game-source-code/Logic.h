#ifndef LOGIC_H
#define LOGIC_H

#include "Scorpion.h"
#include "SfmlDataType.h"
#include "GameDataType.h"
#include "Player.h"
#include "LaserShots.h"
#include "CentipedeHead.h"
#include "GameDataType.h"
#include "MushroomFieldController.h"
#include "Collision.h"
#include "SfmlDataType.h"
#include "Centipede.h"
#include "StopWatch.h"
#include "centipedeAnimation.h"
#include "Spider.h"
#include "SpiderController.h"
#include "DDTBombs.h"
#include "DDTBombsController.h"
#include "ScorpionController.h"

class Logic
{
    public:
    Logic();
    ~Logic();
    Player player_object;
    void update_player(Sprite&);
    shared_ptr<LaserShots>LaserShots_object;
    void updateLaserShots(vector<shared_ptr<Sprite>>&);
    void create_centipede(bool, int, vector<shared_ptr<Sprite>>&);
    vector<shared_ptr<Centipede>>centipede_objectVector;
    void update_centipede(vector<shared_ptr<Sprite>>&);
    //creates objects to be placed in the mushroom field.
    void create_mushrooms();
    void CheckMovementAhead();
    Texture bomb_texture;

    void collisionBetween_mushAndPlayer(Sprite&);
    Texture centipede_texture;
    Texture centipedeBody_texture;
    shared_ptr<MushroomFieldController> GetMushGridPtr() const;

    void collisionBetweenBulletsAndObjects(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);

    void create_bullet(vector<shared_ptr<Sprite>>&);

    int getKilled_segments() const;

    //scorpion watches
    vector<shared_ptr<Scorpion>>scorpion_object_vector;
    vector2f create_scorpion();
    StopWatch scorpion_watch;
    StopWatch scorpion_watch2;

    //set and get if scorpion can be spawned
    bool canSpawn_scorpion();
    void update_scorpion(vector<shared_ptr<Sprite>>&);

    //spider watches
    StopWatch spider_watch;
    //update spider
    void update_spider(vector <shared_ptr<Sprite>>&);
    //vector of shared pointer to spider
    vector<shared_ptr<Spider>>spider_object_vector;
    bool getIfCanSpawnSpider();

    vector2f create_spider();

    //collision between spider and mushroom
    void collision_between_mush_and_spider();

    //collision between player and Spider
    void collision_between_player_and_spider(Sprite&);

    //collision between bullet and spider
    void collision_btwn_bullet_and_spider(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);

    //collision between bomb and bullet
    void collision_between_bullet_and_bomb(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
                                           vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);

    //DDT object vector
    vector <shared_ptr<DDTBombs>>vector_of_bomb_objects;
    bool getIfCanSpawnBomb();

    vector2f create_bomb();

    void update_explosion(vector<shared_ptr<DDTBombs>>&,vector<shared_ptr<Sprite>>&);

    private:
        //Object for the Spider logic and update
        SpiderController spider_control;
        Spider spider;
        centipedeAnimation animation;
        Collision collision;

        //Scorpion
        Scorpion scorpion;
        ScorpionController control_scorpion;

        DDTBombsController bomb_controller;

        //Function to detect mushroom field collisions
        void checkFor_mushroom(shared_ptr<Centipede>&);

        //set centipede sprite movements and rotations
        void Movement(shared_ptr<Centipede>&, shared_ptr<Sprite>&);

        int counter;
        int centipedeSpeed;
        shared_ptr <MushroomFieldController>mushField{new MushroomFieldController{}}; //access to mushroom field

        int playerArea_upBound;
        int centipedeAnimationCounter;

        //variables for centipede creation
        bool isHead;
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

        void movement_update(vector<shared_ptr<Centipede>>&, vector<shared_ptr<Sprite>>&, int);

        // spawn a body segment behind
        void spawn_behind(vector<shared_ptr<Sprite>>&);

        //logic for the centipede
        vector2f pos;

        Texture bullet_texture;

        bool MushCollidedWith_bullet;

        //keep track of shot centipede segments
        int shotCent_segments;
        bool created_scorpion;

        void ChangeToPoison(vector2f);
        float time;

        //a flag for spawning a spider
        bool canSpawnSpider;

        //timer to set when spider gets hungry
        StopWatch lunch_time;

        //DDT bombs
        //check if bomb controller is willing to create a bomb
        //after some certain time
        StopWatch bomb_check;

        //variable to control the selection of scorpion spawn position
        int control;

};

#endif // LOGIC_H
