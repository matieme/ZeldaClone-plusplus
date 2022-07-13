#include "include/Transition.h"

Transition::Transition(float transitionLength)
{
    timer->StartTimer(transitionLength);
    OnEnter();
}

void Transition::OnEnter()
{
    InProgress = true;
}

void Transition::OnUpdate()
{
    if(timer->TimerDone())
    {
        OnEnd();
    }
}

void Transition::OnEnd()
{
    InProgress = false;
}


bool Transition::TransitionInProgress()
{
    return InProgress;
}