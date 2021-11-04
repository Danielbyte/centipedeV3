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


///Collisions Tests
//1.Test between Spider and Mushroom
TEST_CASE("Spider Should eat mushroom if it collides with mushroom when it is hungry and if it is lunch time")
{
    //create a spider object
    auto spider_object = std::make_shared<Spider>();
    //set spider to hungry
    //spider_object -> setToHungry();
    //get the spider's lunch time
    auto lunch_time = spider_object -> getSpider_lunch_time();
    //create a logic instance
    auto logic = Logic{};

    //set the lunch time of the spider(spider can eat if hungryC)
    logic.set_lunch(7.f);

    //get a reference to the last mushroom position
    int row, col;
    auto mushGrid = logic.GetMushGridPtr();
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if( mushGrid -> isMushroom(i,j))
            {
                row = i;
                col = j;
            }
        }
    }

    //set the position of the spider such that it collides with the musroom
    vector2f pos;
    pos.x = col*offset;
    pos.y = row*offset;
    spider_object -> set_position(pos);
    logic.spider_object_vector.push_back(spider_object);

    //set the spider to hungry
    logic.setSpiderToHungry(true);
    //before spider collides with mushroom, mushroom is present
    auto isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

    //update collision
    logic.collision_between_mush_and_spider(true);
    //After spider has eaten the mush
    isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == false);

}

//2
TEST_CASE("Spider Should not eat mushroom if it collides with mushroom when it is not hungry and if it is lunch time")
{
    //create a spider object
    auto spider_object = std::make_shared<Spider>();
    //set spider to hungry
    //spider_object -> setToHungry();
    //get the spider's lunch time
    auto lunch_time = spider_object -> getSpider_lunch_time();
    //create a logic instance
    auto logic = Logic{};

    //set the lunch time of the spider(spider can eat if hungryC)
    logic.set_lunch(7.f);

    //get a reference to the last mushroom position
    int row, col;
    auto mushGrid = logic.GetMushGridPtr();
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if( mushGrid -> isMushroom(i,j))
            {
                row = i;
                col = j;
            }
        }
    }

    //set the position of the spider such that it collides with the musroom
    vector2f pos;
    pos.x = col*offset;
    pos.y = row*offset;
    spider_object -> set_position(pos);
    logic.spider_object_vector.push_back(spider_object);

    //set the spider to hungry
    logic.setSpiderToHungry(false);
    //before spider collides with mushroom, mushroom is present
    auto isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

    //update collision
    logic.collision_between_mush_and_spider(true);
    //Expect mushroom to be there as spider was not hungry
    isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

}

//3
TEST_CASE("Spider Should not eat mushroom if it collides with mushroom when it is not hungry and if it is not lunch time")
{
    //create a spider object
    auto spider_object = std::make_shared<Spider>();
    //set spider to hungry
    //spider_object -> setToHungry();
    //get the spider's lunch time
    auto lunch_time = spider_object -> getSpider_lunch_time();
    //create a logic instance
    auto logic = Logic{};

    //set the lunch time of the spider(spider can eat if hungryC)
    logic.set_lunch(lunch_time - 2);

    //get a reference to the last mushroom position
    int row, col;
    auto mushGrid = logic.GetMushGridPtr();
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if( mushGrid -> isMushroom(i,j))
            {
                row = i;
                col = j;
            }
        }
    }

    //set the position of the spider such that it collides with the musroom
    vector2f pos;
    pos.x = col*offset;
    pos.y = row*offset;
    spider_object -> set_position(pos);
    logic.spider_object_vector.push_back(spider_object);

    //set the spider to hungry
    logic.setSpiderToHungry(false);
    //before spider collides with mushroom, mushroom is present
    auto isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

    //update collision
    logic.collision_between_mush_and_spider(true);
    //Expect mushroom to be there as it was not lunch time
    isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

}

//4
TEST_CASE("Spider Should not eat mushroom if it collides with mushroom when it is hungry and if it is not lunch time")
{
    //create a spider object
    auto spider_object = std::make_shared<Spider>();
    //set spider to hungry
    //spider_object -> setToHungry();
    //get the spider's lunch time
    auto lunch_time = spider_object -> getSpider_lunch_time();
    //create a logic instance
    auto logic = Logic{};

    //set the lunch time of the spider(spider can eat if hungryC)
    logic.set_lunch(lunch_time - 2);

    //get a reference to the last mushroom position
    int row, col;
    auto mushGrid = logic.GetMushGridPtr();
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if( mushGrid -> isMushroom(i,j))
            {
                row = i;
                col = j;
            }
        }
    }

    //set the position of the spider such that it collides with the musroom
    vector2f pos;
    pos.x = col*offset;
    pos.y = row*offset;
    spider_object -> set_position(pos);
    logic.spider_object_vector.push_back(spider_object);

    //set the spider to hungry
    logic.setSpiderToHungry(true);
    //before spider collides with mushroom, mushroom is present
    auto isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

    //update collision
    logic.collision_between_mush_and_spider(true);
    //Expect mushroom to be there as it was not lunch time
    isMush = mushGrid -> isMushroom(row,col);
    CHECK(isMush == true);

}
//5
TEST_CASE("Test collision detection between centipede and player")
{
    Texture player_texture;
    Sprite player_sprite;
    if(!player_texture.loadFromFile("resources/player.png"))throw CouldNotLoadPicture{};
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(vector2f(8.f, 24.f)); //place player at left end row of where centipede is initially spawned
    player_sprite.setOrigin(player_size/2, player_size/2);

    //create a vector of centipede sprite
    vector<shared_ptr<Sprite>>cent_sprite;
    //create Logic instance
    auto logic = Logic{};
    //collision instance
    auto col = Collision{};
    //create the head only
    logic.create_centipede(true, 0, cent_sprite);

    auto cent_iter = cent_sprite.begin();
    auto pos = (*cent_iter) -> getPosition();

    //before update, the two entities have not collided, therefore expect false
    auto isCollided = col.collision_detect(player_sprite.getPosition(),playerWidth,playerHeight, pos, centWidth, centHeight);
    CHECK_FALSE(isCollided);
    //update the centipede 1 times.
    for( auto i = 0; i < 1; i++)
    {
        logic.update_centipede(cent_sprite);
    }
    //get the position of the head after 1 update
    pos = (*cent_iter) -> getPosition();

    //set the player's position to this position so that the collide
    player_sprite.setPosition(pos);
    isCollided = col.collision_detect(player_sprite.getPosition(),playerWidth,playerHeight, pos, centWidth, centHeight);

    //collision should return true
    CHECK(isCollided == true);
}

//6
TEST_CASE("Test if player loses a life after colliding with centipede segment")
{
    Texture player_texture;
    Sprite player_sprite;
    if(!player_texture.loadFromFile("resources/player.png"))throw CouldNotLoadPicture{};
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(vector2f(8.f, 24.f)); //place player at left end row of where centipede is initially spawned
    player_sprite.setOrigin(player_size/2, player_size/2);

    //create a vector of centipede sprite
    vector<shared_ptr<Sprite>>cent_sprite;
    //create Logic instance
    auto logic = Logic{};
    //collision instance
    auto col = Collision{};

    auto player_lives = logic.player_object.getPlayer_lives();

    //before collision, player live are max =3
    CHECK(player_lives == 3);

    //create the head only
    logic.create_centipede(true, 0, cent_sprite);

    auto cent_iter = cent_sprite.begin();
    auto pos = (*cent_iter) -> getPosition();

    //update the centipede 1 time.
    for( auto i = 0; i < 1; i++)
    {
        logic.update_centipede(cent_sprite);
    }
    //get the position of the head after 1 update
    pos = (*cent_iter) -> getPosition();

    //set the player's position to this position so that the collide
    player_sprite.setPosition(pos);

    //update game
    logic.collision_between_centipede_and_player(player_sprite);

    //get player lives after update
    player_lives = logic.player_object.getPlayer_lives();

    //player lives should have decreased
    CHECK(player_lives == 2);
}

//7
TEST_CASE("Test if collision can be detected between player and spider")
{
    Texture player_texture;
    Sprite player_sprite;
    if(!player_texture.loadFromFile("resources/player.png"))throw CouldNotLoadPicture{};
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(vector2f(240.f, 504.f)); //initial pos of player
    player_sprite.setOrigin(player_size/2, player_size/2);

    auto logic = Logic{};
    //create spider
    logic.create_spider();
    auto spider_obj_iter = logic.spider_object_vector.begin();
    //let the two game entities collide
    auto new_spider_pos = player_sprite.getPosition();
    (*spider_obj_iter) -> set_position(new_spider_pos);
    new_spider_pos = (*spider_obj_iter) -> get_position();

    auto col = Collision{};
    auto isCollided = col.collision_detect(player_sprite.getPosition(),playerWidth,playerHeight,new_spider_pos,spiderWidth,spiderHeight);
    CHECK(isCollided == true);

}

//8
TEST_CASE("Test if player looses a life after collision with spider")
{
    Texture player_texture;
    Sprite player_sprite;
    if(!player_texture.loadFromFile("resources/player.png"))throw CouldNotLoadPicture{};
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(vector2f(240.f, 504.f)); //initial pos of player
    player_sprite.setOrigin(player_size/2, player_size/2);

    auto logic = Logic{};
    //create spider
    logic.create_spider();
    auto player_lives = logic.player_object.getPlayer_lives();

    CHECK(player_lives == 3);

    auto spider_obj_iter = logic.spider_object_vector.begin();
    //let the two game entities collide
    auto new_spider_pos = player_sprite.getPosition();
    (*spider_obj_iter) -> set_position(new_spider_pos);
    new_spider_pos = (*spider_obj_iter) -> get_position();

    logic.collision_between_player_and_spider(player_sprite);
    player_lives = logic.player_object.getPlayer_lives();
    CHECK(player_lives == 2);
}

//9
TEST_CASE("Test if Collision is detected between player and flea")
{
    Texture player_texture;
    Sprite player_sprite;
    if(!player_texture.loadFromFile("resources/player.png"))throw CouldNotLoadPicture{};
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(vector2f(240.f, 504.f)); //initial pos of player
    player_sprite.setOrigin(player_size/2, player_size/2);

    auto logic = Logic{};
    //create flea
    logic.create_flea();
    auto flea_iter = logic.flea_object.begin();

    //get the randomly generated flea position
    auto pos = (*flea_iter) -> get_position();

    //set the player to this position so that they collide
    player_sprite.setPosition(pos);

    auto col = Collision{};

    auto isCollided = col.collision_detect(player_sprite.getPosition(), playerWidth,playerHeight,pos,fleaWidth,fleaHeight);
     CHECK(isCollided == true);
}

/*
TEST_CASE("Centipede changes direction when encountered walls"){}

TEST_CASE("Centipede can enter players box"){}
TEST_CASE("Centipede moves up in the box")
TEST_CASE("Centipede is bounded in players box"){}

*/
