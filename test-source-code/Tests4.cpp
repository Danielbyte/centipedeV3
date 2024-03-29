#include "../game-source-code/Player.h"
#include "../game-source-code/Centipede.h"
#include "../game-source-code/mushroomFieldController.h"
#include "../game-source-code/Collision.h"
//#include "../game-source-code/LaserShots.h"
#include "../game-source-code/SfmlDataType.h"
#include "../game-source-code/GameDataType.h"
#include "../game-source-code/Logic.h"
#include "../game-source-code/StopWatch.h"
#include "../game-source-code/DDTBombsController.h"
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
    //auto col = Collision{};
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
    //auto bulletPos = (*bullet_iter) -> getPosition();

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
    //auto col = Collision{};
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
    //auto bulletPos = (*bullet_iter) -> getPosition();

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
    //auto col = Collision{};
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
    //auto bulletPos = (*bullet_iter) -> getPosition();

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
    //auto col = Collision{};
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
    //auto flea_obj_iter = logic.flea_object.begin();
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

TEST_CASE("Test if collision is detected between bullet and bomb")
{
    auto logic = Logic{};
    auto col = Collision{};
    Texture bomb_texture;
    vector<shared_ptr<Sprite>>bullet_sprite;
    vector<shared_ptr<Sprite>>bomb_sprite_vector;

    //query the logic to create a bomb
    logic.create_bullet(bullet_sprite);
    auto pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<Sprite>(Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    bomb_sprite_vector.push_back(bomb_sprite);

    //query the logic to create a bullet
    logic.create_bullet(bullet_sprite);
    auto bullet_iter = bullet_sprite.begin();
    //set position of the bullet such that it collides with the bomb
    (*bullet_iter) -> setPosition(pos);
    auto bulletPos = (*bullet_iter) -> getPosition();
    auto isCollided = col.collision_detect(bulletPos,bulletWidth,bulletHeight,pos,bomb1Width,bomb1Height);

    //expect a collision
    CHECK(isCollided == true);

}

TEST_CASE("Test if bomb is marked for an explosion when it collides with a bullet")
{
    auto logic = Logic{};
    //auto col = Collision{};
    Texture bomb_texture;
    vector<shared_ptr<Sprite>>bullet_sprite;
    vector<shared_ptr<Sprite>>bomb_sprite_vector;

    //query the logic to create a bomb
    logic.create_bullet(bullet_sprite);

    auto pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<Sprite>(Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    bomb_sprite_vector.push_back(bomb_sprite);

    //query the logic to create a bullet
    logic.create_bullet(bullet_sprite);
    auto bullet_iter = bullet_sprite.begin();
    //set position of the bullet such that it collides with the bomb
    (*bullet_iter) -> setPosition(pos);

    //create dummy object sprites to pass in as parameters

    //create a spider
    vector<shared_ptr<Sprite>>spider_sprite;
    //auto pos_ = logic.create_spider();

    //create a centipede
    vector<shared_ptr<Sprite>>centipede_sprite;

    //create a scorpion sprite
    vector<shared_ptr<Sprite>>scorpion_sprite;

    //create a player sprite
    Sprite player_sprite;

    //create a flea sprite
    vector<shared_ptr<Sprite>>flea_sprite;

    //get reference to the bomb object
    auto bomb_obj_iter = logic.vector_of_bomb_objects.begin();

    //before explosion, bomb is not marked to explode
    auto isMarked = (*bomb_obj_iter) -> getIfcanExplode();
    CHECK(isMarked == false);
    logic.collision_between_bullet_and_bomb(bullet_sprite,bomb_sprite_vector,spider_sprite,centipede_sprite,scorpion_sprite,
                                            player_sprite,flea_sprite);

    //after collision with bullet, the bomb should be marked for an explosion
    isMarked = (*bomb_obj_iter) -> getIfcanExplode();
    CHECK(isMarked == true);
}

TEST_CASE("Test if bullet is destroyed when it collides with a bomb")
{
    auto logic = Logic{};
    auto col = Collision{};
    Texture bomb_texture;
    vector<shared_ptr<Sprite>>bullet_sprite;
    vector<shared_ptr<Sprite>>bomb_sprite_vector;

    auto pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<Sprite>(Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    bomb_sprite_vector.push_back(bomb_sprite);

    //query the logic to create a bullet
    logic.create_bullet(bullet_sprite);
    auto bullet_iter = bullet_sprite.begin();
    //set position of the bullet such that it collides with the bomb
    (*bullet_iter) -> setPosition(pos);

    //create dummy object sprites to pass in as parameters

    //create a spider
    vector<shared_ptr<Sprite>>spider_sprite;
    auto pos_ = logic.create_spider();

    //create a centipede
    vector<shared_ptr<Sprite>>centipede_sprite;

    //create a scorpion sprite
    vector<shared_ptr<Sprite>>scorpion_sprite;

    //create a player sprite
    Sprite player_sprite;

    //create a flea sprite
    vector<shared_ptr<Sprite>>flea_sprite;


    //before explosion, there is one created bullet
    auto size = bullet_sprite.size();
    CHECK(size == 1);
    logic.collision_between_bullet_and_bomb(bullet_sprite,bomb_sprite_vector,spider_sprite,centipede_sprite,scorpion_sprite,
                                            player_sprite,flea_sprite);

    //after collision, bullet should be erased from vector
    size = bullet_sprite.size();
    CHECK(size == 0);
}

TEST_CASE("Test if mushroom is destroyed within Explosion radius")
{
    auto logic = Logic{};
    auto bombcontr = DDTBombsController{};
    Texture bomb_texture;
    vector<shared_ptr<Sprite>>bomb_sprite_vector;

    //create bomb at random position
    auto pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<Sprite>(Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    bomb_sprite_vector.push_back(bomb_sprite);

    auto mushField = logic.GetMushGridPtr();
    //place mushroom at top left of bomb
    int row = (int)((pos.y/offset));
    int col = (int)((pos.x/offset));

    mushField -> SpawnMushroomAt_position(row, col);

    auto bomb_iter = bomb_sprite_vector.begin();
    int score = 5;
    bombcontr.explosion_and_mush(*bomb_iter, mushField,score);

    //expect no mushroom at this position
    auto isMushroom = mushField -> isMushroom(row, col);
    CHECK(isMushroom == false);

}

TEST_CASE("Test if spider is destroyed within Explosion radius")
{
    auto logic = Logic{};
    auto bombcontr = DDTBombsController{};
    Texture bomb_texture;
    Texture spider_texture;
    vector<shared_ptr<Sprite>>bomb_sprite_vector;
    vector<shared_ptr<Sprite>>spider_sprite_vector;

    //create bomb at random position
    auto pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<Sprite>(Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    bomb_sprite_vector.push_back(bomb_sprite);

    //Create spider
    vector2f pos_ = logic.create_spider();
    auto spider_sprite = std::make_shared<Sprite>(Sprite());
    if(!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    spider_sprite -> setOrigin(vector2f(0.f,0.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);

    auto spider_iter = spider_sprite_vector.begin();
    (*spider_iter) -> setPosition(pos);

    auto bomb_iter = bomb_sprite_vector.begin();

    int score = 5;
    bombcontr.explosion_and_spider(*bomb_iter,logic.spider_object_vector,spider_sprite_vector, score);
    auto size = spider_sprite_vector.size();
    CHECK(size == 0);
}
