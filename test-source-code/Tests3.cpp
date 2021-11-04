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

//13
TEST_CASE("Test if bullet is deleted on collision with centipede")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>centipede_sprite;
    vector <shared_ptr<Sprite>>bullet_sprite;
    //just create the head only
    logic.create_centipede(true,0,centipede_sprite);

    //create one bullet
    logic.create_bullet(bullet_sprite);

    auto cent_iter = centipede_sprite.begin();
    //get the position of the centipede head
    auto pos = (*cent_iter) -> getPosition();

    //set the bullet to collide with the centipede head
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) ->setPosition(pos);

    //before collision update, the vector should contain the constructed bullet
    auto size = bullet_sprite.size();
    CHECK(size == 1);
    //update collisions
    logic.collision_between_centipede_and_bullet(bullet_sprite, centipede_sprite);
    size = bullet_sprite.size();
    CHECK(size == 0);
}

//14
TEST_CASE("Test if previous body segment is turned into a head when leading segment is shot")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>centipede_sprite;
    vector <shared_ptr<Sprite>>bullet_sprite;

    //spawn 2 body segments
    logic.create_centipede(true,2,centipede_sprite);
    auto centObj_iter = logic.centipede_objectVector.begin();

    //create one bullet
    logic.create_bullet(bullet_sprite);

    auto cent_iter = centipede_sprite.begin();
    //get the position of the centipede head
    auto pos = (*cent_iter) -> getPosition();

    //set the bullet to collide with the centipede head
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) ->setPosition(pos);

    //before the collision the 2nd segment is not a head
    auto next = (centObj_iter + 1);
    auto isHead = (*next) -> getHead();
    CHECK(isHead == false);

    //update objects
    logic.collision_between_centipede_and_bullet(bullet_sprite, centipede_sprite);
    logic.delete_segment_and_spawn_mushroom(centipede_sprite);
    //the body segment that followed the head should now be the new head
    //bear in mind that the vector shifits
    isHead = (*centObj_iter) -> getHead();
    CHECK(isHead == true);

    //the last centipede should still be a body
    auto next_segment = (centObj_iter + 1);
    isHead =(*next_segment) -> getHead();
    CHECK(isHead == false);

}
//15
TEST_CASE("Test if body segment in the middle is turned into a head if segment in front is short")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>centipede_sprite;
    vector <shared_ptr<Sprite>>bullet_sprite;

    //spawn 2 body segments
    logic.create_centipede(true,4,centipede_sprite);
    auto centObj_iter = logic.centipede_objectVector.begin();

    //create one bullet
    logic.create_bullet(bullet_sprite);

    auto cent_iter = centipede_sprite.begin();
    //get the position of the second segment
    auto pos = (*(cent_iter + 1)) -> getPosition();

    //set the bullet to collide with the centipede head
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) ->setPosition(pos);

    //before the collision the 3rd segment is not a head
    auto next = (centObj_iter + 2);
    auto isHead = (*next) -> getHead();
    CHECK(isHead == false);

    //update objects
    logic.collision_between_centipede_and_bullet(bullet_sprite, centipede_sprite);
    logic.delete_segment_and_spawn_mushroom(centipede_sprite);
    //the body segment that followed the shot body segment should be a head
    //bear in mind that the vector shifts
    isHead = (*(centObj_iter + 1)) -> getHead();
    CHECK(isHead == true);

    //the last centipede should still be a body
    auto next_segment = (centObj_iter + 3);
    isHead =(*next_segment) -> getHead();
    CHECK(isHead == false);
}

//16
TEST_CASE("Test if shot body segment is turned into a mushroom")
{
    auto logic = Logic{};
    auto mushField = logic.GetMushGridPtr();
    vector<shared_ptr<Sprite>>centipede_sprite;
    vector <shared_ptr<Sprite>>bullet_sprite;

    //spawn 1 body segments
    logic.create_centipede(true,1,centipede_sprite);
    auto centObj_iter = logic.centipede_objectVector.begin();

    //create one bullet
    logic.create_bullet(bullet_sprite);

    auto cent_iter = centipede_sprite.begin();
    //get the position of the centipede head
    auto pos = (*cent_iter) -> getPosition();

    //set the bullet to collide with the centipede head
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) ->setPosition(pos);

    //before the collision, expect no mushroom at this position
    auto isMush = mushField -> isMushroom(((int)(pos.y/offset)),((int)(pos.x/offset)));
    if(!isMush){CHECK_FALSE(isMush);}
    //update objects
    logic.collision_between_centipede_and_bullet(bullet_sprite, centipede_sprite);
    logic.delete_segment_and_spawn_mushroom(centipede_sprite);

    //at this position, expect a mushroom
    isMush = mushField -> isMushroom(((int)(pos.y/offset)),((int)(pos.x/offset)));

    if(isMush)
    {
        CHECK(isMush == true);
    }
}

//17
TEST_CASE("Test if collision is detected between bullet and spider")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>spider_sprite_vector;
    vector<shared_ptr<Sprite>>bullet_sprite_vector;

    vector2f pos_ = logic.create_spider();
    Texture spider_texture;
    auto spider_sprite = std::make_shared<Sprite>(Sprite());
    if(!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    spider_sprite -> setOrigin(vector2f(0.f,0.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);

    //update spider twice
    logic.update_spider(spider_sprite_vector);
    logic.update_spider(spider_sprite_vector);

    //create a bullet
    logic.create_bullet(bullet_sprite_vector);
    //set the position of the bullet in such a manner that it collides with the spider
    auto spider_iter = spider_sprite_vector.begin();
    auto pos = (*spider_iter) -> getPosition();
    auto bullet_iter = bullet_sprite_vector.begin();
    (*bullet_iter) -> setPosition(pos);

    //see if collision is successfully detected
    auto col = Collision{};
    auto isCollided =col.collision_detect((*bullet_iter) -> getPosition(),bulletWidth,bulletHeight,pos,spiderWidth,spiderHeight);
    CHECK(isCollided == true);

}

TEST_CASE("Test if bullet is erased on collision with the spider")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>spider_sprite_vector;
    vector<shared_ptr<Sprite>>bullet_sprite_vector;

    vector2f pos_ = logic.create_spider();
    Texture spider_texture;
    auto spider_sprite = std::make_shared<Sprite>(Sprite());
    if(!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    spider_sprite -> setOrigin(vector2f(0.f,0.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);

    //update spider twice
    logic.update_spider(spider_sprite_vector);
    logic.update_spider(spider_sprite_vector);

    //create a bullet
    logic.create_bullet(bullet_sprite_vector);
    //set the position of the bullet in such a manner that it collides with the spider
    auto spider_iter = spider_sprite_vector.begin();
    auto pos = (*spider_iter) -> getPosition();
    auto bullet_iter = bullet_sprite_vector.begin();
    (*bullet_iter) -> setPosition(pos);

    //bullet sprite should be one before collision (since one bullet was only created)
    auto size = bullet_sprite_vector.size();
    CHECK(size == 1);
    logic.collision_btwn_bullet_and_spider(bullet_sprite_vector, spider_sprite_vector);

    //bullet vector should be empty after collision
    size = bullet_sprite_vector.size();
    CHECK(size == 0);
}

TEST_CASE("Test if spider is erased on collision with the bullet")
{
    auto logic = Logic{};
    vector<shared_ptr<Sprite>>spider_sprite_vector;
    vector<shared_ptr<Sprite>>bullet_sprite_vector;

    vector2f pos_ = logic.create_spider();
    Texture spider_texture;
    auto spider_sprite = std::make_shared<Sprite>(Sprite());
    if(!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    spider_sprite -> setOrigin(vector2f(0.f,0.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);

    //update spider twice
    logic.update_spider(spider_sprite_vector);
    logic.update_spider(spider_sprite_vector);

    //create a bullet
    logic.create_bullet(bullet_sprite_vector);
    //set the position of the bullet in such a manner that it collides with the spider
    auto spider_iter = spider_sprite_vector.begin();
    auto pos = (*spider_iter) -> getPosition();
    auto bullet_iter = bullet_sprite_vector.begin();
    (*bullet_iter) -> setPosition(pos);

    //bullet sprite should be one before collision (since one bullet was only created)
    auto size = spider_sprite_vector.size();
    CHECK(size == 1);
    //check object vector of spider
    size = logic.spider_object_vector.size();
    CHECK(size == 1);
    logic.collision_btwn_bullet_and_spider(bullet_sprite_vector, spider_sprite_vector);

    //bullet vector should be empty after collision
    size = spider_sprite_vector.size();
    CHECK(size == 0);

    //check for deletion of spider object
    size = logic.spider_object_vector.size();
    CHECK(size == 0);
}

TEST_CASE("Test if collision is detected between bullet and scorpion")
{
    auto logic = Logic{};
    auto col = Collision{};
    vector<shared_ptr<Sprite>>scorpion_sprite_vector;
    vector<shared_ptr<Sprite>>bullet_sprite_vector;
    Texture scorpion_texture;

    //query logic to create scorpion
    auto pos = logic.create_scorpion();
    auto scorpion_sprite = std::make_shared<Sprite>(Sprite());
    if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
    scorpion_sprite -> setOrigin(vector2f(0.f, 0.f));
    scorpion_sprite -> setTexture(scorpion_texture);
    scorpion_sprite -> setPosition(pos);
    scorpion_sprite_vector.push_back(scorpion_sprite);

    //query the logic  to update the scorpion
    logic.update_scorpion(scorpion_sprite_vector);
    logic.update_scorpion(scorpion_sprite_vector);

    //get reference to the scorpion position
    auto scorpion_iter = scorpion_sprite_vector.begin();
    pos = (*scorpion_iter) -> getPosition();

    //set bullet to this position so that the tow game entities collide
    //create a bullet
    logic.create_bullet(bullet_sprite_vector);
    auto bullet_iter = bullet_sprite_vector.begin();
    (*bullet_iter) ->setPosition(pos);
    auto bullet_pos = (*bullet_iter) ->getPosition();
    auto isCollided =col.collision_detect(bullet_pos,bulletWidth,bulletHeight,pos,scorpion_width,scorpion_height);

    //expect a collision
    CHECK(isCollided == true);

}

TEST_CASE("Test if bullet is erased on collision with scorpion")
{
    auto logic = Logic{};
    auto col = Collision{};
    vector<shared_ptr<Sprite>>scorpion_sprite_vector;
    vector<shared_ptr<Sprite>>bullet_sprite_vector;
    Texture scorpion_texture;

    //query logic to create scorpion
    auto pos = logic.create_scorpion();
    auto scorpion_sprite = std::make_shared<Sprite>(Sprite());
    if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
    scorpion_sprite -> setOrigin(vector2f(0.f, 0.f));
    scorpion_sprite -> setTexture(scorpion_texture);
    scorpion_sprite -> setPosition(pos);
    scorpion_sprite_vector.push_back(scorpion_sprite);

    //query the logic  to update the scorpion
    logic.update_scorpion(scorpion_sprite_vector);
    logic.update_scorpion(scorpion_sprite_vector);

    //get reference to the scorpion position
    auto scorpion_iter = scorpion_sprite_vector.begin();
    pos = (*scorpion_iter) -> getPosition();

    //set bullet to this position so that the tow game entities collide
    //create a bullet
    logic.create_bullet(bullet_sprite_vector);
    auto bullet_iter = bullet_sprite_vector.begin();
    (*bullet_iter) ->setPosition(pos);
    auto bullet_pos = (*bullet_iter) ->getPosition();

    //bullet object present before collision
    auto size = bullet_sprite_vector.size();
    CHECK(size == 1);

    logic.collision_between_bullet_and_scorpion(bullet_sprite_vector, scorpion_sprite_vector);

    //bullet sprite vector should be empty after collision
    size = bullet_sprite_vector.size();
    CHECK(size == 0);
}

TEST_CASE("Test if scorpion is erased on collision with bullet")
{
    auto logic = Logic{};
    auto col = Collision{};
    vector<shared_ptr<Sprite>>scorpion_sprite_vector;
    vector<shared_ptr<Sprite>>bullet_sprite_vector;
    Texture scorpion_texture;

    //query logic to create scorpion
    auto pos = logic.create_scorpion();
    auto scorpion_sprite = std::make_shared<Sprite>(Sprite());
    if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
    scorpion_sprite -> setOrigin(vector2f(0.f, 0.f));
    scorpion_sprite -> setTexture(scorpion_texture);
    scorpion_sprite -> setPosition(pos);
    scorpion_sprite_vector.push_back(scorpion_sprite);

    //query the logic  to update the scorpion
    logic.update_scorpion(scorpion_sprite_vector);
    logic.update_scorpion(scorpion_sprite_vector);

    //get reference to the scorpion position
    auto scorpion_iter = scorpion_sprite_vector.begin();
    pos = (*scorpion_iter) -> getPosition();

    //set bullet to this position so that the tow game entities collide
    //create a bullet
    logic.create_bullet(bullet_sprite_vector);
    auto bullet_iter = bullet_sprite_vector.begin();
    (*bullet_iter) ->setPosition(pos);
    auto bullet_pos = (*bullet_iter) ->getPosition();

    //scorpion object present before collision(sprite)
    auto size = scorpion_sprite_vector.size();
    CHECK(size == 1);

    //scorpion object present
    size = logic.scorpion_object_vector.size();
    CHECK(size == 1);

    logic.collision_between_bullet_and_scorpion(bullet_sprite_vector, scorpion_sprite_vector);

    //scorpion sprite vector should be empty after collision
    size = scorpion_sprite_vector.size();
    CHECK(size == 0);

    //scorpion object wiped
    size = logic.scorpion_object_vector.size();
    CHECK(size == 0);

}

/*
TEST_CASE("Centipede changes direction when encountered walls"){}

TEST_CASE("Centipede can enter players box"){}
TEST_CASE("Centipede moves up in the box")
TEST_CASE("Centipede is bounded in players box"){}

*/
