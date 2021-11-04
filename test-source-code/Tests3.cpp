#include "../game-source-code/Player.h"
#include "../game-source-code/Centipede.h"
#include "../game-source-code/mushroomFieldController.h"
#include "../game-source-code/Collision.h"
//#include "../game-source-code/LaserShots.h"
#include "../game-source-code/SfmlDataType.h"
#include "../game-source-code/GameDataType.h"
#include "../game-source-code/Logic.h"
#include "../game-source-code/StopWatch.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
//11
TEST_CASE("Test if centipede segment is set to inactive after collision with bullet")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>centipede_sprite;
    vector <shared_ptr<Sprite>>bullet_sprite;
    //just create the head only
    logic.create_centipede(true,0,centipede_sprite);
    auto cent_obj_iter = logic.centipede_objectVector.begin();

    //create one bullet
    logic.create_bullet(bullet_sprite);

    auto cent_iter = centipede_sprite.begin();
    //get the position of the centipede head
    auto pos = (*cent_iter) -> getPosition();

    //set the bullet to collide with the centipede head
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) ->setPosition(pos);

    //before collision, the segment status is active
    auto isActive = (*cent_obj_iter) -> getSegment_status();
    CHECK(isActive == true);

    //update collisions
    logic.collision_between_centipede_and_bullet(bullet_sprite, centipede_sprite);
    isActive = (*cent_obj_iter) -> getSegment_status();

    //after collision with centipede, centipede segment should be set to inactive
    CHECK(isActive == false);

}

//12
TEST_CASE("Test if shot centipede segment that was marked is deleted")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>centipede_sprite;
    vector <shared_ptr<Sprite>>bullet_sprite;
    //just create the head only
    logic.create_centipede(true,0,centipede_sprite);
    auto cent_obj_iter = logic.centipede_objectVector.begin();

    //create one bullet
    logic.create_bullet(bullet_sprite);

    auto cent_iter = centipede_sprite.begin();
    //get the position of the centipede head
    auto pos = (*cent_iter) -> getPosition();

    //set the bullet to collide with the centipede head
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) ->setPosition(pos);

    //update collisions
    logic.collision_between_centipede_and_bullet(bullet_sprite, centipede_sprite);

    //before deletion, the vector size should be 1, as one segment as created
    //Sprite vector
    auto size = centipede_sprite.size();
    CHECK(size == 1);

    //centipede object vecto
    size = logic.centipede_objectVector.size();
    CHECK(size == 1);

    //update vectors for deletions
    logic.delete_segment_and_spawn_mushroom(centipede_sprite);

    //centipede sprites vector should be empty
    auto empty_vector = centipede_sprite.size();
    CHECK(empty_vector == 0);
    //centipede object vector should be empty
    empty_vector = logic.centipede_objectVector.size();
    CHECK(empty_vector == 0);

}

/*
TEST_CASE("Centipede changes direction when encountered walls"){}

TEST_CASE("Centipede can enter players box"){}
TEST_CASE("Centipede moves up in the box")
TEST_CASE("Centipede is bounded in players box"){}

*/
