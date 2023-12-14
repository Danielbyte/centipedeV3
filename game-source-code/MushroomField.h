#ifndef MUSHROOMFIELD_H
#define MUSHROOMFIELD_H

#include "GameDataType.h"


class MushroomField
{
public:
    MushroomField(int, int);
    //Randomly populate the field with mushrooms
    //void populate();
    float get_Xpos();
    float get_Ypos();

    //Decrement and update mush health if hit my mushroom
    void decrementMush_health();
    //get mush health
    int getMush_health() const;

    bool getIsPoisoned() const;
    void changeToPoison();

private:
    float x_position;
    float y_position;
    int mushroom_health;
    //see if mushroom is poisoned
    bool isPoisoned;
};
#endif // MUSHROOMFIELD_H
