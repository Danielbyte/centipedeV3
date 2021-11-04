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

TEST_CASE("Test if bullet is erased on collision with flea")
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

    auto size = bullet_sprite.size();
    //One bullet present
    CHECK(size == 1);
    logic.collision_between_bullet_and_flea(bullet_sprite, flea_sprite_vector);

    //after collision, there should be no bullet
    size = bullet_sprite.size();
    CHECK(size == 0);
}

TEST_CASE("Test if flea lives are decremented after shot")
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
    auto flea_obj_iter = logic.flea_object.begin();
    //get reference to the flea position
    auto flea_iter = flea_sprite_vector.begin();
    pos = (*flea_iter) -> getPosition();

    //give this position to the bullet so that they collisde
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) -> setPosition(pos);
    auto bulletPos = (*bullet_iter) -> getPosition();

    //flea lives before collision are max
    auto flea_lives = (*flea_obj_iter) -> get_flea_health();
    CHECK(flea_lives == 2);
    logic.collision_between_bullet_and_flea(bullet_sprite, flea_sprite_vector);
    //after collision, decreased flea lives
    flea_lives = (*flea_obj_iter) -> get_flea_health();
    CHECK(flea_lives == 1);

}

TEST_CASE("Test if flea speed doubles after one shot")
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
    auto flea_obj_iter = logic.flea_object.begin();
    //get reference to the flea position
    auto flea_iter = flea_sprite_vector.begin();
    pos = (*flea_iter) -> getPosition();

    //give this position to the bullet so that they collisde
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) -> setPosition(pos);
    auto bulletPos = (*bullet_iter) -> getPosition();

    //flea lives before collision are max
    auto flea_speed1 = (*flea_obj_iter) -> get_flea_speed();
    logic.collision_between_bullet_and_flea(bullet_sprite, flea_sprite_vector);
    //after collision, decreased flea lives
    auto flea_speed2 = (*flea_obj_iter) -> get_flea_speed();
    CHECK(flea_speed2 == 2*flea_speed1);

}

TEST_CASE("Test if flea is eliminated after two player shots")
{
    auto logic = Logic{};
    auto col = Collision{};
    Texture flea_texture;
    vector<shared_ptr<Sprite>>bullet_sprite;
    vector<shared_ptr<Sprite>>flea_sprite_vector;

    //create 2 bullet;
    logic.create_bullet(bullet_sprite);
    logic.create_bullet(bullet_sprite);

    //two bullets before collision
    auto size = bullet_sprite.size();
    CHECK(size == 2);

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
    auto flea_obj_iter = logic.flea_object.begin();
    //get reference to the flea position
    auto flea_iter = flea_sprite_vector.begin();
    pos = (*flea_iter) -> getPosition();

    //give this position to the bullet so that they collisde
    auto bullet_iter = bullet_sprite.begin();
    (*bullet_iter) -> setPosition(pos);
    auto bulletPos = (*bullet_iter) -> getPosition();

    //flea lives before collision are max
    logic.collision_between_bullet_and_flea(bullet_sprite, flea_sprite_vector);
    size = flea_sprite_vector.size();
    //flea is still alive, so vector size = 1;
    CHECK(size == 1);
    //flea object
    size = logic.flea_object.size();
    //size should be 1 also
    CHECK(size == 1);

    // there should be one bullet remaining
    size = bullet_sprite.size();
    CHECK(size == 1);

    //update flee pos
    logic.update_flea(flea_sprite_vector);
    pos = (*flea_iter) -> getPosition();
    //update bullet
    bullet_iter = bullet_sprite.begin();
    (*bullet_iter) -> setPosition(pos);
    bulletPos = (*bullet_iter) -> getPosition();

    //update collisions
    logic.collision_between_bullet_and_flea(bullet_sprite, flea_sprite_vector);

    //flea object should be wiped
    size = flea_sprite_vector.size();
    CHECK(size == 0);

    //all bullets wiped
    size = bullet_sprite.size();
    CHECK(size == 0);

}

/*
TEST_CASE("Centipede changes direction when encountered walls"){}

TEST_CASE("Centipede can enter players box"){}
TEST_CASE("Centipede moves up in the box")
TEST_CASE("Centipede is bounded in players box"){}

*/
