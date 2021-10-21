#ifndef CENTIPEDEBODY_H
#define CENTIPEDEBODY_H
#include "GameDataType.h"
#include "CentipedeHead.h"

class CentipedeBody : public CentipedeBaseClass
{
    public:
        CentipedeBody(float, float,CentipedeHead*);
        CentipedeBody* GetNextBodySegment() const;
        CentipedeBody* GetBodySegmentInfront() const;
        CentipedeHead* GetHead() const;
        void setBodySegmentInfront(CentipedeBody* ptr);
        void setNextBodySegment(CentipedeBody* ptr);
        void setHead(CentipedeHead* ptr);
        void update_body();
        void check_head();
        void check_body();

        //get body positions
        float get_Xpos() const;
        float get_Ypos() const;
    private:
        //CentipedeHead* head;
        float xBody_pos;
        float yBody_pos;
        Direction next_direction;
        Direction current_direction;
};
#endif // CENTIPEDEBODY_H
