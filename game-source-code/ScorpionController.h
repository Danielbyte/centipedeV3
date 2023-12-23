#ifndef SCORPIONCONTROLLER_H
#define SCORPIONCONTROLLER_H

#include "GameDataType.h"
#include "Scorpion.h"
#include "Collision.h"
#include "mushroomResources.h"

class ScorpionController
{
public:
    ScorpionController(){};
    void update_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>&,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    sf::Texture scorpion_texture;
    sf::Vector2f position_to_spawn_scorpion();
    Collision collision;
    

private:
    sf::Vector2f pos;
    void animate_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<sf::Sprite>>&);
    void poison_mushroom(sf::Vector2f pos_, vector<shared_ptr<MushroomField>>& mushField,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    shared_ptr<MushroomResources> mushroom_resource = std::make_shared<MushroomResources>();
};
#endif // SCORPIONCONTROLLER_H
