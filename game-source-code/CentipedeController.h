#ifndef CENTIPEDECONTROLLER_H
#define CENTIPEDECONTROLLER_H

#include "Centipede.h"
#include "GameDataType.h"
#include "centipedeAnimation.h"
#include "MushroomField.h"

class CentipedeController
{
public:
    CentipedeController();
    void update_centipede(vector<shared_ptr<Centipede>>&, vector<shared_ptr<Sprite>>&, 
        vector<shared_ptr<MushroomField>>& mushField);
private:
    centipedeAnimation animation;
    void checkFor_mushroom(shared_ptr<Centipede>&, vector<shared_ptr<MushroomField>>& mushField);
    void Movement(shared_ptr<Centipede>&, shared_ptr<Sprite>&);
    float playerArea_upBound;

};
#endif // CENTIPEDECONTROLLER_H
