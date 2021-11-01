#ifndef FLEACONTROLLER_H
#define FLEACONTROLLER_H

#include "Flea.h"
#include "GameDataType.h"
#include "SfmlDataType.h"
#include "mushroomFieldController.h"

class FleaController
{
private:
    FleaController();
    void update_flea(vector<shared_ptr<Flea>>&,vector<shared_ptr<Sprite>>&,shared_ptr<MushroomFieldController>&);
public:
    void spawn_mushroom(const float&, const float&, shared_ptr<MushroomFieldController>&);
    bool set_if_can_spawn_flea(shared_ptr<MushroomFieldController>&);

};
#endif // FLEACONTROLLER_H
