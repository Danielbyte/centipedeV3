#ifndef SCORPIONCONTROLLER_H
#define SCORPIONCONTROLLER_H

#include "GameDataType.h"
#include "Scorpion.h"
#include "Collision.h"
#include "mushroomResources.h"

class ScorpionController
{
public:
    ScorpionController();
    void update_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<sf::Sprite>>&, vector<shared_ptr<MushroomField>>&,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    sf::Vector2f position_to_spawn_scorpion();
    
private:
    sf::Vector2f pos;
    Collision collision;
    void animate_scorpion(vector<shared_ptr<Scorpion>>&, vector<shared_ptr<sf::Sprite>>&);
    void poison_mushroom(sf::Vector2f pos_, vector<shared_ptr<MushroomField>>& mushField,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    shared_ptr<MushroomResources> mushroom_resource = std::make_shared<MushroomResources>();
    void load_resources();

    sf::Texture scorpion1_t, scorpion2_t, scorpion3_t, scorpion4_t;
    sf::Texture death1_t, death2_t, death3_t, death4_t, death5_t, death6_t;
    float deathFramePeriod;
};
#endif // SCORPIONCONTROLLER_H
