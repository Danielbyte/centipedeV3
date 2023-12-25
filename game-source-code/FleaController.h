#ifndef FLEACONTROLLER_H
#define FLEACONTROLLER_H

#include "Flea.h"
#include "GameDataType.h"
#include "MushroomField.h"
#include "mushroomResources.h"

class FleaController
{
public:
    FleaController();
    void update_flea(vector<shared_ptr<Flea>>&,vector<shared_ptr<sf::Sprite>>&,vector<shared_ptr<MushroomField>>&,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites);
    bool set_if_can_spawn_flea(vector<shared_ptr<MushroomField>>&);
    sf::Vector2f generate_spawn_position();

private:
    void spawn_mushroom(sf::Vector2f, vector<shared_ptr<MushroomField>>&,
        vector<shared_ptr<sf::Sprite>>& mushroom_sprites);

    void animate_flea(shared_ptr<Flea>&, shared_ptr<sf::Sprite>&);
    //minimum mushrooms that can be at player area
    int min_mushrooms;

    shared_ptr<MushroomResources>mushroom_resource = std::make_shared<MushroomResources>();
    int previousYpos;

    void load_resources();
    sf::Texture flea1_t, flea2_t, flea3_t, flea4_t;
    sf::Texture death1_t, death2_t, death3_t, death4_t, death5_t, death6_t;
    float deathFramePeriod;
};
#endif // FLEACONTROLLER_H
