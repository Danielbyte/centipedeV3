#ifndef MUSHROOMFIELDCONTROLLER_H
#define MUSHROOMFIELDCONTROLLER_H

#include "MushroomField.h"
#include "GameDataType.h"
#include "ctime"
class MushroomField;

class MushroomFieldController
{
public:
    MushroomFieldController();
    ~MushroomFieldController();
    void create_mushrooms();

    //Function to signify if position has a mushroom
    bool isMushroom(int, int);

    MushroomField* mushArray[32][30];

    //Function to spawn mushroom at specified position
    void SpawnMushroomAt_position(int, int);

    //prevent unintentional copy construction
    MushroomFieldController(const MushroomFieldController&) = delete;
    MushroomFieldController& operator = (const MushroomFieldController&) = delete;

private:

//    vectOfMush_field mushrooms_;

    //variable to control the frequency of
    //randomly placing mushroom.
    //The higher this number = more mushrooms spawned
    int percentage_chance;
    //int** mushArray;

};
#endif // MUSHROOMFIELDCONTROLLER_H
