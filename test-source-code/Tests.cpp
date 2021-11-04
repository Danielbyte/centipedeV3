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

//PLAYER TESTS
TEST_CASE("Test if player position is correctly set and retrieved")
{
    auto player = Player{};
    // initial x coordinate of player object
    player.set_Xposition(200);
    // initial y coordinate of player object
    player.set_Yposition(500);
    //player.set_position(new_position);
    CHECK(200== player.get_Xposition());
    CHECK(500 == player.get_Yposition());
}
TEST_CASE("Test if player object is initially at bottom center")
{
    auto player = Player{};
    // initial x coordinate of player object
    auto xCoordinate = 240;
    // initial y coordinate of player object
    auto yCoordinate = 504;
    //player.set_position(new_position);
    CHECK(xCoordinate == player.get_Xposition());
    CHECK(yCoordinate == player.get_Yposition());
}
TEST_CASE("Test if player object speed correctly set")
{
    auto player = Player{};
    player.setPlayer_speed(5);

    CHECK(5 == player.getPlayer_speed());
}
///PLAYER MOVEMENT TESTS
TEST_CASE("Information of an object can be changed and correctly returned")
{
    auto player = Player{};
    player.setPlayer_movement(Direction::Up, true);
    CHECK(player.getPlayer_movement(Direction::Up));

    player.setPlayer_movement(Direction::Down, true);
    CHECK(player.getPlayer_movement(Direction::Down));

    player.setPlayer_movement(Direction::Right, true);
    CHECK(player.getPlayer_movement(Direction::Right));

    player.setPlayer_movement(Direction::Left, true);
    CHECK(player.getPlayer_movement(Direction::Left));

}

/// Player is restricted within
TEST_CASE("Player is restricted within boundaries")
{
    auto player = Player{};
    //Left bounds
    player.set_Xposition(8);
    player.setPlayer_movement(Direction::Left, true);
    CHECK(player.get_Xposition()==8);
    //Right bounds
    player.set_Xposition(472);
    player.setPlayer_movement(Direction::Right, true);
    CHECK(player.get_Xposition()==472);
    //UP bounds
    player.set_Yposition(376);
    player.setPlayer_movement(Direction::Up, true);
    CHECK(player.get_Yposition()==376);
    //down bounds
    player.set_Yposition(504);
    player.setPlayer_movement(Direction::Down, true);
    CHECK(player.get_Yposition()==504);
}

///CENTIPEDE TESTS
//Centipede creation tests
TEST_CASE("Centipede object can be set")
{

    auto centipede_=Centipede{};

    centipede_.setHead(true);
    CHECK(centipede_.getHead());
}

TEST_CASE("Centipede position can be correctly placed and retreived")
{

    auto centipede_=Centipede{};
    auto new_position = vector2f{200, 300};
    centipede_.set_position(new_position);

    CHECK(centipede_.get_position().x==200);
    CHECK(centipede_.get_position().y==300);
}

TEST_CASE("Centipede object is initially placed  in the top centre of screen")
{
    auto centipede_=Centipede{};

    centipede_.setHead(true);
    CHECK(centipede_.get_position().x==(232));        // this is a (480/2)-12 we have to change this so the numbers ar =e not so random
    CHECK(centipede_.get_position().y==24);         // 24 is the centre of sprite from y exis

}
// Cenipede Movement tests
TEST_CASE("Centipede speed can be set and retrieved")
{

    auto centipede_=Centipede{};

    centipede_.setCentipedeSpeed(8);

    CHECK(centipede_.getCentipede_speed());
}
//R,L,D,U
TEST_CASE("Centipede object moves right")
{

    auto centipede_=Centipede{};

    auto initial_pos=centipede_.get_position().x;
    centipede_.move_right();
    auto final_pos= centipede_.get_position().x;

    CHECK(initial_pos<final_pos);

}

TEST_CASE("Centipede object moves left ")
{
    auto centipede_=Centipede{};
    auto initial_pos=centipede_.get_position().x;
    centipede_.move_left();
    auto final_pos= centipede_.get_position().x;

    CHECK(initial_pos>final_pos);
}

TEST_CASE("Centipede object moves up")
{
    auto centipede_=Centipede{};
    auto initial_pos=centipede_.get_position().y;
    centipede_.move_up();
    auto final_pos= centipede_.get_position().y;

    CHECK(initial_pos>final_pos);
}

TEST_CASE("Centipede object moves down")
{
    auto centipede_=Centipede{};
    auto initial_pos=centipede_.get_position().y;
    centipede_.move_down();  //move up represents going down
    auto final_pos= centipede_.get_position().y;

    CHECK(initial_pos<final_pos);
}

TEST_CASE("Check if collision is detected between centipede and Lasershot")
{
    vector2d centipedePos_;
    vector2d laserPos_;
    auto collision_ = Collision{};
    auto centipede_ = Centipede{};
    auto laserShots_ = LaserShots(64,112,2);
    //set position for centipede segment
    centipede_.set_position(vector2f(64,109));
    //move centipede downwards by one row towards the bullet(so that they collide)
    centipede_.move_down();
    //get the new position of the centipede
    auto centPosition =centipede_.get_position();
    centipedePos_.x = centPosition.x;
    centipedePos_.y = centPosition.y;
    //getting position of the bullet
    auto laserPosition = laserShots_.getBullet_direction();
    laserPos_.x = laserPosition.x;
    laserPos_.y = laserPosition.y;
    // check the collisions between the two
    auto isCollided = collision_.isCollidedWithBullet(laserPos_,bullet_size,centipedePos_,centipedeBody_size);
    CHECK(isCollided);
}


//Test Boundaries and movement
TEST_CASE("Centipede is bounded by right walls")
{

    auto centipede_=Centipede{};
    auto new_position = vector2f{480, 0};
    centipede_.set_position(new_position);
    centipede_.move_right();
    CHECK(centipede_.get_position().x==480);       // This shows it bounces and moves back by a block

}


//Mushroom tests
TEST_CASE("Check if mushroom health decrement")
{

    vector2d mushroomPos_;
    vector2d laserPos_;
    auto collision_ = Collision{};
    auto mushroom_ = MushroomField(80,128);
    //assume a collision between mushroom and bullet
    mushroom_.decrementMush_health();
    auto mushHealth = mushroom_.getMush_health();
    CHECK(mushHealth==3);

}
TEST_CASE("Check if mushroom is destroyed after 4 shoots")
{
    int row, col;

    auto logicObj_ = Logic{};
    auto mushGrid = logicObj_.GetMushGridPtr();
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if( mushGrid -> isMushroom(i,j))
            {
                row = i;
                col = j;
                return;

            }
        }
    }
    CHECK(mushGrid -> isMushroom(row,col) == true);
    mushGrid -> mushArray[row][col] -> decrementMush_health();
    mushGrid-> mushArray[row][col] -> decrementMush_health();
    mushGrid -> mushArray[row][col] -> decrementMush_health();
    mushGrid -> mushArray[row][col] -> decrementMush_health();
    //After 4 bullets hits, mushroom health must = 0
    if ((mushGrid -> mushArray[row][col] -> getMush_health()) == 0)
    {

        mushGrid -> mushArray[row][col] = NULL;
    }


    CHECK_FALSE(mushGrid -> isMushroom(row,col));
}

///stop watch tests
TEST_CASE("Test for non negative time at initialization of stopwatch object")
{
    auto watch = StopWatch{};
    auto initial_time = watch.getTimeElapsed();
    CHECK(initial_time == 0);
}

TEST_CASE("Test if stopwatch can restart")
{
    auto watch = StopWatch{};

    auto t1 = .5;//set 1 second
    while(watch.getTimeElapsed() < t1)
    {
        //do nothing for 1 seconds
    }
    watch.restart();
    auto new_time = watch.getTimeElapsed();
    CHECK(new_time == 0); //expect new time to be zero after restart

}

TEST_CASE("Test if time can be stopped")
{
    auto watch = StopWatch{};
    auto t1 = watch.getTimeElapsed();
    for(auto i= 0; i < 4; i++)
    {
        //wait for some time
    }

    watch.stop(); //stop timer

        for(auto i= 0; i < 4; i++)
    {
        //wait for some time again
    }

    auto t2 = watch.getTimeElapsed();
//t1 and t2 should be equal since the timer was stopped
    CHECK(t1 == t2);
}
/*
TEST_CASE("Centipede changes direction when encountered walls"){}

TEST_CASE("Centipede can enter players box"){}
TEST_CASE("Centipede moves up in the box")
TEST_CASE("Centipede is bounded in players box"){}

*/
