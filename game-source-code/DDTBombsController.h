#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include "ctime"
#include "GameDataType.h"
#include "DDTBombs.h"
#include "Collision.h"
#include "Spider.h"
#include "Centipede.h"
#include "Scorpion.h"
#include "Player.h"
#include "Flea.h"
#include "mushroomResources.h"

class DDTBombsController
{
public:
    DDTBombsController();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
    void generate_position();
    sf::Vector2f getGeneratedPosition() const;
    sf::Texture bomb_texture;
    void Explosion(vector<shared_ptr<DDTBombs>>&,vector<shared_ptr<sf::Sprite>>&,
        vector<shared_ptr<MushroomField>>& mushField, vector<shared_ptr<MushroomResources>>& mushroo_sprites,vector<shared_ptr<Spider>>&,
        vector<shared_ptr<sf::Sprite>>&,vector<shared_ptr<Centipede>>&,vector<shared_ptr<sf::Sprite>>&,
        vector<shared_ptr<Scorpion>>&,vector<shared_ptr<sf::Sprite>>&,Player&,sf::Sprite&, 
        vector<shared_ptr<Flea>>&, vector<shared_ptr<sf::Sprite>>&, int&);

//made public for test puropses
    void explosion_and_mush(shared_ptr<sf::Sprite>&,vector<shared_ptr<MushroomField>>&, vector<shared_ptr<MushroomResources>>& mushroom_sprites, int&);
    void explosion_and_spider(shared_ptr<sf::Sprite>&,vector<shared_ptr<Spider>>&, vector<shared_ptr<sf::Sprite>>&, int&);
    void explosion_and_centipede(shared_ptr<sf::Sprite>&, vector<shared_ptr<Centipede>>&, vector<shared_ptr<sf::Sprite>>&, int &);
    void explosion_and_scorpion(shared_ptr<sf::Sprite>&,vector<shared_ptr<Scorpion>>& ,vector<shared_ptr<sf::Sprite>>&, int&);
    void explosion_and_player(shared_ptr<sf::Sprite>&, Player&, sf::Sprite&);
    void explosion_and_flea(shared_ptr<sf::Sprite>&, vector<shared_ptr<Flea>>&, vector<shared_ptr<sf::Sprite>>&, int&);

private:
    Collision collision;
    sf::Vector2f pos;
    bool canCreateBomb;

    //Quadrant collisions(General this one)
    bool fourth_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f,float, float,bool&);
    bool third_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f, float, float, bool&);
    bool second_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f,float,float, bool&);
    bool first_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f,float,float, bool&);

    //Quadrant collisions specific to mushrooms
    bool fourth_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f, float, float,int&);
    bool third_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f, float, float,int&);
    bool second_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f, float, float,int&);
    bool first_quadrant_collisions(sf::Vector2f, float, float, sf::Vector2f, float, float,int&);
};
#endif // DDTBOMBSCONTROLLER_H
