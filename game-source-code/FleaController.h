#ifndef FLEACONTROLLER_H
#define FLEACONTROLLER_H

#include "Flea.h"
#include "GameDataType.h"
#include "MushroomField.h"

class FleaController
{
public:
    FleaController();
    void update_flea(vector<shared_ptr<Flea>>&,vector<shared_ptr<sf::Sprite>>&,vector<shared_ptr<MushroomField>>&);
    bool set_if_can_spawn_flea(vector<shared_ptr<MushroomField>>&);
    sf::Vector2f generate_spawn_position();
    sf::Texture flea_texture;

private:
    void spawn_mushroom(sf::Vector2f, vector<shared_ptr<MushroomField>>&);

    void animate_flea(shared_ptr<Flea>&, shared_ptr<sf::Sprite>&);
    //minimum mushrooms that can be at player area
    int min_mushrooms;

};
#endif // FLEACONTROLLER_H
