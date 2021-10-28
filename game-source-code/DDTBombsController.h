#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include <ctime>

class DDTBombsController
{
public:
    DDTBombs();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
private:
    bool canCreateBomb;
};
#endif // DDTBOMBSCONTROLLER_H
