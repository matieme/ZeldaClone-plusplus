#pragma once
#include "include/InputManager.h"
#include "include/LevelManager.h"

enum PlayerState
{
    IDLE,
    RUN
};

class Player
{
public:
    void Update(InputManager& InputManagerInst);
    Player();
    ~Player();
    void Destroy();

private:
    void Move(InputManager& InputManagerInst);
    void Draw();
    void ChangeSpriteViewDirection(Input Direction);
    float Speed{1.7};
    Rectangle LinkRect;
    Rectangle LinkRectCollider;
    bool CheckMapColliders();
    LevelManager& LevelManagerInstance = LevelManager::GetManager();
    void DrawPlayerCollider(Input Direction);
};