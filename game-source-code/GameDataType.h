#ifndef GAMEDATATYPE_H
#define GAMEDATATYPE_H
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>

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

const auto mushHeight = 16;
const auto mushWidth = 16;

const auto spiderHeight = 16;
const auto spiderWidth = 30;

const auto playerWidth = 16;
const auto playerHeight = 16;

//Define game objects
enum class ID{player_, centipede};

// Defines movement of player
enum class Direction {unknown, Up, Down, Left,Right};

class CouldNotLoadPicture{};
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
