#include "include/Timer.h"

float LifeTime;
float StartTime;

Timer::Timer()
{
    LifeTime = 0;
}

void Timer::StartTimer(float lifeTime)
{
    StartTime = GetTime();
    LifeTime = lifeTime;
}

bool Timer::TimerDone()
{
    return GetTime() - StartTime >= LifeTime;
}