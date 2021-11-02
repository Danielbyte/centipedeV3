#ifndef FLEACONTROLLER_H
#define FLEACONTROLLER_H

#include "Flea.h"
#include "GameDataType.h"
#include "SfmlDataType.h"
#include "mushroomFieldController.h"
#include "MushroomField.h"

class FleaController
{
public:
    FleaController();
    void update_flea(vector<shared_ptr<Flea>>&,vector<shared_ptr<Sprite>>&,shared_ptr<MushroomFieldController>&);
    bool set_if_can_spawn_flea(shared_ptr<MushroomFieldController>&);
    vector2f generate_spawn_position();
    Texture flea_texture;

private:
    void spawn_mushroom(vector2f, shared_ptr<MushroomFieldController>&);

    void animate_flea(shared_ptr<Flea>&, shared_ptr<Sprite>&);
    //minimum mushrooms that can be at player area
    int min_mushrooms;

};
#endif // FLEACONTROLLER_H
