#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <ctime>

class StopWatch
{
public:
    StopWatch();
    float getTimeElapsed();
    void stop();
    void restart();

private:
    float current_time();
    float start_time;
    float stop_time;

};
#endif // STOPWATCH_H
