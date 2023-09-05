#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include "ctime"
#include "GameDataType.h"
#include "DDTBombs.h"
#include "SfmlDataType.h"
#include "Collision.h"
#include "Spider.h"
#include "Centipede.h"
#include "Scorpion.h"
#include "Player.h"
#include "Flea.h"

class DDTBombsController
{
public:
    DDTBombsController();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
    void generate_position();
    vector2f getGeneratedPosition() const;
    Texture bomb_texture;
    void Explosion(vector<shared_ptr<DDTBombs>>&,vector<shared_ptr<Sprite>>&,
        vector<shared_ptr<MushroomField>>& mushField,vector<shared_ptr<Spider>>&,
        vector<shared_ptr<Sprite>>&,vector<shared_ptr<Centipede>>&,vector<shared_ptr<Sprite>>&,
        vector<shared_ptr<Scorpion>>&,vector<shared_ptr<Sprite>>&,Player&,Sprite&, 
        vector<shared_ptr<Flea>>&, vector<shared_ptr<Sprite>>&, int&);

//made public for test puropses
    void explosion_and_mush(shared_ptr<Sprite>&,vector<shared_ptr<MushroomField>>&, int&);
    void explosion_and_spider(shared_ptr<Sprite>&,vector<shared_ptr<Spider>>&, vector<shared_ptr<Sprite>>&, int&);
    void explosion_and_centipede(shared_ptr<Sprite>&, vector<shared_ptr<Centipede>>&, vector<shared_ptr<Sprite>>&, int &);
    void explosion_and_scorpion(shared_ptr<Sprite>&,vector<shared_ptr<Scorpion>>& ,vector<shared_ptr<Sprite>>&, int&);
    void explosion_and_player(shared_ptr<Sprite>&, Player&, Sprite&);
    void explosion_and_flea(shared_ptr<Sprite>&, vector<shared_ptr<Flea>>&, vector<shared_ptr<Sprite>>&, int&);

private:
    Collision collision;
    vector2f pos;
    bool canCreateBomb;

    //Quadrant collisions(General this one)
    bool fourth_quadrant_collisions(vector2f, float, float, vector2f,float, float,bool&);
    bool third_quadrant_collisions(vector2f, float, float, vector2f, float, float, bool&);
    bool second_quadrant_collisions(vector2f, float, float, vector2f,float,float, bool&);
    bool first_quadrant_collisions(vector2f, float, float, vector2f,float,float, bool&);

    //Quadrant collisions specific to mushrooms
    bool fourth_quadrant_collisions(vector2f, float, float, vector2f, float, float,int&);
    bool third_quadrant_collisions(vector2f, float, float, vector2f, float, float,int&);
    bool second_quadrant_collisions(vector2f, float, float, vector2f, float, float,int&);
    bool first_quadrant_collisions(vector2f, float, float, vector2f, float, float,int&);
};
#endif // DDTBOMBSCONTROLLER_H
