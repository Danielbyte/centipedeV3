#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include "ctime"
#include "GameDataType.h"
#include "DDTBombs.h"
#include "mushroomFieldController.h"
#include "SfmlDataType.h"
#include "Collision.h"
#include "Spider.h"
#include "Centipede.h"

class DDTBombsController
{
public:
    DDTBombsController();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
    void generate_position(shared_ptr<MushroomFieldController>&);
    vector2f getGeneratedPosition() const;
    Texture bomb_texture;
    void Explosion(vector<shared_ptr<DDTBombs>>&,vector<shared_ptr<Sprite>>&,shared_ptr<MushroomFieldController>&,vector<shared_ptr<Spider>>&,
                   vector<shared_ptr<Sprite>>&,vector<shared_ptr<Centipede>>&,vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);

private:
    Collision collision;
    vector2f pos;
    bool canCreateBomb;
    void explosion_and_mush(shared_ptr<Sprite>&, shared_ptr<MushroomFieldController>&);
    void explosion_and_spider(shared_ptr<Sprite>&,vector<shared_ptr<Spider>>&, vector<shared_ptr<Sprite>>&);
    void explosion_and_centipede(shared_ptr<Sprite>&, vector<shared_ptr<Centipede>>&, vector<shared_ptr<Sprite>>&);
    void explosion_and_scorpion(shared_ptr<Sprite>&, vector<shared_ptr<Sprite>>&);

    //Quadrant collisions(General this one)
    bool fourth_quadrant_collisions(vector2f, float, float, vector2f, float, float, bool&);
    bool third_quadrant_collisions(vector2f, float, float, vector2f, float, float, bool&);
    bool second_quadrant_collisions(vector2f, float, float, vector2f, float, float, bool&);
    bool first_quadrant_collisions(vector2f, float, float, vector2f, float, float, bool&);

    //Quadrant collisions specific to mushrooms
    void fourth_quadrant_collisions(vector2f, float, float, vector2f, float, float, int, int, shared_ptr<MushroomFieldController>&);
    void third_quadrant_collisions(vector2f, float, float, vector2f, float, float, int, int, shared_ptr<MushroomFieldController>&);
    void second_quadrant_collisions(vector2f, float, float, vector2f, float, float, int, int, shared_ptr<MushroomFieldController>&);
    void first_quadrant_collisions(vector2f, float, float, vector2f, float, float, int, int, shared_ptr<MushroomFieldController>&);
};
#endif // DDTBOMBSCONTROLLER_H
