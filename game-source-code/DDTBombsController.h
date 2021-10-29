#ifndef DDTBOMBSCONTROLLER_H
#define DDTBOMBSCONTROLLER_H

#include "ctime"
#include "GameDataType.h"
#include "DDTBombs.h"

class DDTBombsController
{
public:
    DDTBombsController();
    bool getIfCanCreateBomb() const;
    void setIfCanCreateBomb();
private:
    bool canCreateBomb;
};
#endif // DDTBOMBSCONTROLLER_H
