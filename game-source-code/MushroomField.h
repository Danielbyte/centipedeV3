#ifndef MUSHROOMFIELD_H
#define MUSHROOMFIELD_H

#include "GameDataType.h"
#include "mushroomFieldController.h"

class MushroomFieldController;

class MushroomField
{
public:
    MushroomField(int, int);
    //overload equal operator
    //~MushroomField();

    //prevent copy construction
    MushroomField(const MushroomField&) = delete;
    MushroomField& operator = (const MushroomField&) = delete;
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
   // MushroomFieldController* ptr;
    float horizontalPos;
    float verticalPos;
    int mushroom_health;
    //see if mushroom is poisoned
    bool isPoisoned;
};
#endif // MUSHROOMFIELD_H
