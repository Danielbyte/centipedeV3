#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "GameDataType.h"
#include "SfmlDataType.h"

class Centipede
{
public:
    Centipede();
    //Functions to set centipede movement
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void set_position(vector2f position);
    void set_Xpos (vector2f position_);
    void set_Ypos(vector2f _position);
    // get centipede piece position
    vector2f get_position() const;

    int getCentipede_speed () const;

    void setHead(bool head_);
    bool getHead() const;

    void setIsMovingUp(bool);
    void setIsMovingDown(bool);
    void setMoveUp(bool);
    void setMoveDown(bool);

    void setCentipedeSpeed(int speed);

    bool getIsMovingUp() const;
    bool getIsMovingDown() const;
    bool getMoveUp() const;
    bool getMoveDown() const;

    void setUpdate_counter(int);
    int getUpdate_counter() const;
    void resetUpdate_counter();
    //get is segment is dead or alive
    bool getSegment_status() const;

    //set segment status
    void setSegment_status(bool);

    void set_counter(int);
    int get_counter() const;
    void reset_counter();


private:
    vector2f pos;
    int centipede_speed;
    bool head;

    float x_initial;
    float y_initial;

    //booleans to mark behavior
    bool isMovingUp;
    bool isMovingDown;
    bool moveDown;
    bool moveUp;

    int update_counter;
    //variable to get state of segment
    bool isActive;
    int counter;

};
#endif // CENTIPEDE_H
