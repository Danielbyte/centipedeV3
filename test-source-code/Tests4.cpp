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

TEST_CASE("Test if collision is detected between bullet and flea")
{
    auto logic = Logic{};
    auto col = Collision{};
    Texture flea_texture;
    vector<shared_ptr<Sprite>>bullet_sprite;
    vector<shared_ptr<Sprite>>flea_sprite_vector;

    //create bullet;
    logic.create_bullet(bullet_sprite);

    //create flea
    auto flea_sprite = std::make_shared<Sprite>(Sprite());
    auto pos = logic.create_flea();
    if(!flea_texture.loadFromFile("resources/flea1.png")) throw CouldNotLoadPicture{};
    flea_sprite ->setTexture(flea_texture);
    flea_sprite -> setOrigin(vector2f(0.f,0.f));
    flea_sprite -> setPosition(pos);
    flea_sprite_vector.push_back(flea_sprite);

    //update the flea twice
    logic.update_flea(flea_sprite_vector);
    logic.update_flea(flea_sprite_vector);

    //get reference to the flea position
    auto flea_iter = flea_sprite_vector.begin();
    pos = (*flea_iter) -> getPosition();

    //give this position to the bullet so that they collisde
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) -> setPosition(pos);
    auto bulletPos = (*bullet_iter) -> getPosition();

    auto isCollided = col.collision_detect(bulletPos,bulletWidth,bulletHeight,pos,fleaWidth,fleaHeight);
    //expect a collision

    CHECK(isCollided == true);
}


/*
TEST_CASE("Centipede changes direction when encountered walls"){}

TEST_CASE("Centipede can enter players box"){}
TEST_CASE("Centipede moves up in the box")
TEST_CASE("Centipede is bounded in players box"){}

*/
