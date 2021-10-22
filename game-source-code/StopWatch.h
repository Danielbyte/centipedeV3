#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <ctime>

class StopWatch
{
public:
    StopWatch();
    float getTimeElapsed() const;
    void stop();
    void restart();

private:
    float TimeTaken_ForEvent();
    float start_time;
    float stop_time;

};
#endif // STOPWATCH_H
