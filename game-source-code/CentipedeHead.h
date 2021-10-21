#ifndef CENTIPEDEHEAD_H
#define CENTIPEDEHEAD_H
#include "GameDataType.h"
#include "SfmlDataType.h"
#include "CentipedeNode.h"
#include "CentipedeBody.h"
#include "mushroomFieldController.h"

class CentipedeHead : public CentipedeBaseClass
{
public:
    CentipedeHead(int, bool, shared_ptr<MushroomFieldController>&);
    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void set_Xposition(float);
    void set_Yposition(float);
    float get_Xposition() const;
    float get_Yposition() const;
    float get_centipedeSpeed() const;
    void spawn_body(int body_segments);
    void setNextBodySegment(CentipedeBody* ptr);

    //Getters and setters to monitor centipede movement
    bool get_left() const;
    bool get_right() const;
    bool get_up() const;
    bool get_down() const;

    //Update centipede
    void Update();

    void mark_movement();
    void check_mushroom();

private:
    //Logic logic;
    float x_position;
    float y_position;
    unsigned long centipede_speed;

    //booleans for head's logic
    bool up;
    bool down;
    bool left;
    bool right;
    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingUp;
    bool isMovingDown;

    CentipedeBody* body_ptr;

    shared_ptr <MushroomFieldController>mushGridPtr;
};
#endif // CENTIPEDEHEAD_H
