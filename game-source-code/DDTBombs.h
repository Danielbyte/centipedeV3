#ifndef DDTBOMBS_H
#define DDTBOMBS_H

#include "SfmlDataType.h"

class DDTBombs
{
public:
    DDTBombs(vector2f);
    //define What happens at destruction of an object
    ~DDTBombs();

    vector2f get_position() const;
    void set_position(vector2f);
    int getNumberOfBombs() const;
private:
    vector2f pos;

    //keep track of the number of bombs
    static int number_of_bombs;

};
#endif // DDTBOMBS_H
