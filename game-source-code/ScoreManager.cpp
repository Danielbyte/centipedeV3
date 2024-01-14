#include "ScoreManager.h"

int Scoremanager::highScoreDisplay(int current_score)
{
    //error handling, non negative score
    if(current_score < 0) throw NegativeScore{};
    high_score_file.open("resources/Highscore.txt");

    //update the score if previous high score is murred
    if(high_score_file.is_open())
    {
        high_score_file >> high_score;
        if(high_score <= current_score)
        {
            high_score = current_score;
        }
    }

    high_score_file.close();
    output.open("resources/Highscore.txt");
    if(output.is_open())
    {
        output << high_score;
    }

    output.close();
    return high_score;
}

void Scoremanager::reset_high_score()
{
    high_score = 0;

    high_score_file.close();
    output.open("resources/Highscore.txt");
    if(output.is_open())
    {
        output << high_score;
    }

    output.close();
}

int Scoremanager::getHighScore() const
{
    return high_score;
}
