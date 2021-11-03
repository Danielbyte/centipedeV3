#ifndef GAMEDATATYPE_H
#define GAMEDATATYPE_H
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>

const auto windowWidth = 480ul;
const auto windowHeight = 512ul;
const auto player_size = 16;
const auto X_enemy_size = 16;
const auto Y_enemy_size = 16;
const auto offset = 16;
const auto Tile_offset = 8;
const auto mushroom_size = 16;
const auto centipedeBody_size = 16;
const auto bullet_size = 16;
const auto scorpion_width = 32;
const auto scorpion_height = 16;
const auto bullet_offset = 1;
const auto flea_spawn_chance = 50;

const auto mushHeight = 16;
const auto mushWidth = 16;

const auto centWidth = 16;
const auto centHeight = 16;

const auto spiderHeight = 16;
const auto spiderWidth = 30;

const auto playerWidth = 16;
const auto playerHeight = 16;

const auto bulletWidth = 2;
const auto bulletHeight = 16;
const auto bomb1Height = 16;
const auto bomb1Width = 16;
const auto bomb2Width = 32;
const auto bomb2Height = 32;
const auto bomb3Width = 48;
const auto bomb3Height = 48;
const auto bomb4Width = 64;
const auto bomb4Height = 64;
const auto bomb5Width = 80;
const auto bomb5Height = 80;
const auto bomb6Width = 96;
const auto bomb6Height = 96;
const auto lastHeight = 32;
const auto lastWidth = 32;

const auto fleaWidth = 16;
const auto fleaHeight = 16;

const auto spiderPoints = 300;
const auto fleaPoints = 200;
const auto scorpionPoints = 1000;
const auto mushroomPoints = 1;
const auto headPoints = 100;
const auto bodyPoints = 10;

//Define game objects
enum class ID{player_, centipede};

// Defines movement of player
enum class Direction {unknown, Up, Down, Left,Right};

class CouldNotLoadPicture{};
class NegativeScore{};
using std::vector;
using std::shared_ptr;

//General purpose 2D vector
class vector2d
{
public:
    float x;
    float y;
};

class object_info
{
public:
    ID identifier;
    vector2d position;
};

class Object_properties
{
public:
    vector2d center;
    vector2d object_size;
};

#endif // GAMEDATATYPE_H
