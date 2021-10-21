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
    //MushroomField(MushroomField& therField) = delete;
   // MushroomField& operator = (const MushroomField& otherField) = delete;
    //~MushroomField();

    //Randomly populate the field with mushrooms
    //void populate();
    float get_Xpos();
    float get_Ypos();

    //Decrement and update mush health if hit my mushroom
    void decrementMush_health();
    //get mush health
    int getMush_health() const;

private:
    float x_position;
    float y_position;
    MushroomFieldController* ptr;
    float horizontalPos;
    float verticalPos;
    int mushroom_health;
};
//vector of shared pointers to keep track of all objects in the mushroom field.
//typedef vector<shared_ptr<MushroomField>> vectOfMush_field;
#endif // MUSHROOMFIELD_H
