#ifndef GAME_H
#define GAME_H
#include "ScreenManager.h"
#include "ScoreManager.h"

class Game
{
    public:
    //player will have 3 lives
    void run_game();

    private:
        Scoremanager manage_score;
};
#endif // GAME_H
