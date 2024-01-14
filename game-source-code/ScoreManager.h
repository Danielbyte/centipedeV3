#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "GameDataType.h"
using namespace std;

class Scoremanager
{
public:

    Scoremanager(){};
    int highScoreDisplay(int current_score);
    void reset_high_score();
    int getHighScore() const;

private:
    int high_score;
    ifstream high_score_file;
    ofstream output;


};
#endif // SCOREMANAGER_H
