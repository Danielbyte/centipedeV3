#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include "ctime"
#include "GameDataType.h"
#include "DDTBombs.h"
#include "mushroomFieldController.h"
#include "SfmlDataType.h"

class DDTBombsController
{
public:
    DDTBombsController();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
    void generate_position(shared_ptr<MushroomFieldController>&);
    vector2f getGeneratedPosition() const;
    Texture bomb_texture;
private:
    vector2f pos;
    bool canCreateBomb;
};
#endif // DDTBOMBSCONTROLLER_H
