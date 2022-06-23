#pragma once
#include "include/InputManager.h"

class Player
{
public:
    void Update(InputManager& InputManagerInst);
    Player();
    ~Player();
    void Destroy();

private:
    void Move(InputManager& InputManagerInst);
};