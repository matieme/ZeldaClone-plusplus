#pragma once
#include "raylib.h"

class Timer
{
public:
    Timer();
    void StartTimer(float lifeTime);
    void UpdateTimer();
    bool TimerDone();

};