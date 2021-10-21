#ifndef CENTIPEDENODE_H
#define CENTIPEDEHEAD_H

#include "GameDataType.h"
#include "SfmlDataType.h"

class CentipedeHead;
class CentipedeBody;

class CentipedeBaseClass
{
//base class for CentipedeHead and CentipedeBody classes
public:
    //constructor does nothing
    CentipedeBaseClass(){};
    virtual void ChangeBodyToHead();
    virtual void SpawnMushroom();

    //pointers to create a linked list of centipede object
    CentipedeHead* head_ptr;
    CentipedeBody* next; //next
    CentipedeBody* ahead_ptr;

    vector2f pos;
    float counter;
    float counter2;
};

#endif // CENTIPEDENODE_H
