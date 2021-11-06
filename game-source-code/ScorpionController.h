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
    vector2f position_to_spawn_scorpion();

private:
    vector2f pos;
    void animate_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<Sprite>>&);
    void poison_mushroom(vector2f, shared_ptr<MushroomFieldController>&);
};
#endif // SCORPIONCONTROLLER_H
