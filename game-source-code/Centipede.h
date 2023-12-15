#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "GameDataType.h"
#include "SfmlDataType.h"
#include "gameResources.h"

class Centipede : public GameResources
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
    void resetCounter2();

    //sets and getters for mark movement booleans
    bool getUp() const;
    bool getDown() const;
    bool getLeft() const;
    bool getRight() const;

    bool getWasMovingLeft() const;
    bool getWasMovingRight() const;
    bool getWasMovingUp() const;
    bool getWasMovingDown() const;

    void setUp(bool);
    void setDown(bool);
    void setLeft(bool);
    void setRight(bool);

    void setWasMovingLeft(bool);
    void setWasMovingRight(bool);
    void setWasMovingUp(bool);

    void setWasMovingDown(bool);
    int getCounter2() const;

    bool getIsCentipedePoisoned() const;
    void setToPoisoned();
    void cure_from_poison();

    void increment_animation();
    int get_anime_loop() const;
    void reset_animation_loop();

    //get is segment hit by explosion
    bool get_is_hit() const;

    //set segment if hit by explosion
    void is_hit(bool);

    void setRotation(float _rotation);
    float getRotation() const;

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

    //get if centipede is poisoned
    bool isCentipedePoisoned;

    //set Animation
    int animation_loop;

    //mark segment if is hit by explosion
    bool isHit;

    float rotation;
};
#endif // CENTIPEDE_H
