#ifndef SCORPIONCONTROLLER_H
#define SCORPIONCONTROLLER_H

#include "SfmlDataType.h"
#include "GameDataType.h"
#include "Scorpion.h"
#include "Collision.h"

class ScorpionController
{
public:
    ScorpionController(){};
    void update_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<Sprite>>&, vector<shared_ptr<MushroomField>>&);
    Texture scorpion_texture;
    vector2f position_to_spawn_scorpion();
    Collision collision;
    

private:
    vector2f pos;
    void animate_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<Sprite>>&);
    void poison_mushroom(vector2f, vector<shared_ptr<MushroomField>>&);
};
#endif // SCORPIONCONTROLLER_H
