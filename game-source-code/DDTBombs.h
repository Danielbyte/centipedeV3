#ifndef DDTBOMBS_H
#define DDTBOMBS_H

#include "SfmlDataType.h"

class DDTBombs
{
public:
    DDTBombs();
    //define What happens at destruction of an object
    //~DDTBombs();

    vector2f get_position() const;
    void set_position(vector2f);
    int getNumberOfBombs() const;
    void setExplosion(bool);
    bool getIfcanExplode() const;
    void increment_counter();
    int get_counter() const;
    void reset_counter();
private:
    vector2f pos;
    bool canExplode;
    //variable to create animations
    int counter;

    //keep track of the number of bombs
    static int number_of_bombs;

};
#endif // DDTBOMBS_H
