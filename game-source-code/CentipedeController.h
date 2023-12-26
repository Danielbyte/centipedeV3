#ifndef CENTIPEDECONTROLLER_H
#define CENTIPEDECONTROLLER_H

#include "Centipede.h"
#include "centipedeAnimation.h"
#include "MushroomField.h"

class CentipedeController
{
public:
    CentipedeController();
    void update_centipede(vector<shared_ptr<Centipede>>&, vector<shared_ptr<sf::Sprite>>&, 
        vector<shared_ptr<MushroomField>>& mushField);
private:
    centipedeAnimation animation;
    void checkFor_mushroom(shared_ptr<Centipede>&, vector<shared_ptr<MushroomField>>& mushField);
    void Movement(shared_ptr<Centipede>&, shared_ptr<sf::Sprite>&);
    void load_resources();
    float playerArea_upBound;

    sf::Texture head1_t, head2_t, head3_t, head4_t, head5_t, head6_t, head7_t, head8_t;

    //centipede body textures
    sf::Texture body1_t, body2_t, body3_t, body4_t, body5_t, body6_t, body7_t, body8_t;
    sf::Texture death1_t, death2_t, death3_t, death4_t, death5_t, death6_t;

    float deathFramePeriod;

    void updateSegmentTexture(shared_ptr<sf::Sprite>& segment_sprite, shared_ptr<Centipede>& centipede_segment);

};
#endif // CENTIPEDECONTROLLER_H
