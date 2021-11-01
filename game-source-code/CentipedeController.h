#ifndef CENTIPEDECONTROLLER_H
#define CENTIPEDECONTROLLER_H

#include "Centipede.h"
#include "GameDataType.h"
#include "centipedeAnimation.h"
#include "mushroomFieldController.h"


class CentipedeController
{
public:
    CentipedeController();
    void update_centipede(vector<shared_ptr<Centipede>>&, vector<shared_ptr<Sprite>>&, shared_ptr<MushroomFieldController>&);
private:
    centipedeAnimation animation;
    void checkFor_mushroom(shared_ptr<Centipede>&, shared_ptr<MushroomFieldController>&);
    void Movement(shared_ptr<Centipede>&, shared_ptr<Sprite>&);
    float playerArea_upBound;

};
#endif // CENTIPEDECONTROLLER_H
