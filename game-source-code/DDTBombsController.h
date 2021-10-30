#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include "ctime"
#include "GameDataType.h"
#include "DDTBombs.h"
#include "mushroomFieldController.h"
#include "SfmlDataType.h"
#include "Collision.h"

class DDTBombsController
{
public:
    DDTBombsController();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
    void generate_position(shared_ptr<MushroomFieldController>&);
    vector2f getGeneratedPosition() const;
    Texture bomb_texture;
    void Explosion(vector<shared_ptr<DDTBombs>>&,vector<shared_ptr<Sprite>>&,shared_ptr<MushroomFieldController>&);

private:
    Collision collision;
    vector2f pos;
    bool canCreateBomb;
    void explosion_and_mush(shared_ptr<Sprite>&, shared_ptr<MushroomFieldController>&);
};
#endif // DDTBOMBSCONTROLLER_H
