#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

class Scoremanager
{
public:

    Scoremanager(){};
    int highScoreDisplay(int current_score);

private:
    int high_score;
    ifstream high_score_file;
    ofstream output;


};
#endif // SCOREMANAGER_H
