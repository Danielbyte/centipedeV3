#ifndef SCORPIONCONTROLLER_H
#define SCORPIONCONTROLLER_H

#include "SfmlDataType.h"
#include "GameDataType.h"
#include "Scorpion.h"
#include "mushroomFieldController.h"

class ScorpionController
{
public:
    ScorpionController(){};
    void update_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<Sprite>>&, shared_ptr<MushroomFieldController>&);
    Texture scorpion_texture;

private:
    vector2f pos;
    //variable for animation
};
#endif // SCORPIONCONTROLLER_H
