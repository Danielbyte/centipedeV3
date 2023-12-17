#ifndef SCORPIONCONTROLLER_H
#define SCORPIONCONTROLLER_H

#include "GameDataType.h"
#include "Scorpion.h"
#include "Collision.h"

class ScorpionController
{
public:
    ScorpionController(){};
    void update_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>&);
    sf::Texture scorpion_texture;
    sf::Vector2f position_to_spawn_scorpion();
    Collision collision;
    

private:
    sf::Vector2f pos;
    void animate_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<sf::Sprite>>&);
    void poison_mushroom(sf::Vector2f pos_, vector<shared_ptr<MushroomField>>& mushField);
};
#endif // SCORPIONCONTROLLER_H
