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

    void setCentipedeSpeed(int speed);

    //get is segment is dead or alive
    bool getSegment_status() const;

    //set segment status
    void setSegment_status(bool);

    void increment_counter();
    int get_counter() const;
    void reset_counter();

    void incrementCounter2();
    int getCounter2() const;
    void resetCounter2();

    bool getDown() const;
    bool getUp() const;

private:
    vector2f pos;
    int centipede_speed;
    bool head;

    float x_initial;
    float y_initial;

    //booleans to mark behavior of centipede
    bool up;
    bool down;
    bool left;
    bool right;
    bool wasMovingLeft;
    bool wasMovingRight;
    bool wasMovingUp;
    bool wasMovingDown;


    //int update_counter;
    //variable to get state of segment
    bool isActive;
    //counter to update down/up movement of centipede
    int counter;

    //counter to update collisions of centipede
     int counter2;



};
#endif // CENTIPEDE_H
