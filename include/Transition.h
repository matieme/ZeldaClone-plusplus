#pragma once
#include "include/Timer.h"

class Transition
{
public:
    Transition(float transitionLength);
    bool TransitionInProgress();
    void OnEnter();
    void OnUpdate();
    void OnEnd();

private:
    Timer* timer;
    bool InProgress;
};