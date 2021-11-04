#include "StopWatch.h"

StopWatch::StopWatch():
    stop_time{0}
    {
        start_time = current_time();
    }

float StopWatch::current_time()
{
    auto time = clock();
    return static_cast<float>(time)/CLOCKS_PER_SEC;
}

float StopWatch::getTimeElapsed()
{
    stop();
    auto elapsed_time = stop_time - start_time;
    return elapsed_time;
}

void StopWatch::stop()
{
    stop_time = current_time();
}

void StopWatch::restart()
{
    start_time = current_time();
}

float StopWatch::getTimeElapsed(float t)
{
    return t;
}
