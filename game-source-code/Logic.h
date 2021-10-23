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
#include "Scorpion.h"
#include "StopWatch.h"

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

    void collisionBetween_mushAndPlayer(Sprite&);
    Texture centipede_texture;
    Texture centipedeBody_texture;
    shared_ptr<MushroomFieldController> GetMushGridPtr() const;

    void collisionBetweenBulletsAndObjects(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);

    void create_bullet(vector<shared_ptr<Sprite>>&);

    int getKilled_segments() const;

    //scorpion
    vector2f create_scorpion();
    StopWatch scorpion_watch;
    StopWatch scorpion_watch2;
    //set and get if scorpion can be spawned
    bool canSpawn_scorpion();
    void update_scorpion(shared_ptr<Sprite>&);

    private:
        //int index;
        int counter;
        int centipedeSpeed;
        shared_ptr <MushroomFieldController>mushField{new MushroomFieldController{}}; //access to mushroom field
        //vectOfMush_field mushroom;
        //void getMushroomField_vectors();
        //int** mushArray = 0;

        Collision collision;
        Scorpion scorpion;
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
       /*bool up;
        bool down;
        bool left;
        bool right;
        bool isMovingLeft;
        bool isMovingRight;
        bool isMovingUp;
        bool isMovingDown;
        Direction _down;
        Direction _up;
        Direction _left;
        Direction _right;
        Direction nextMovement;
        Direction next_nextMovement;*/

        Texture bullet_texture;

        bool MushCollidedWith_bullet;

        //keep track of shot centipede segments
        int shotCent_segments;
        bool created_scorpion;

};
