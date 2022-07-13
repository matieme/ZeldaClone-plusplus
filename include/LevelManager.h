#pragma once
#include "include/MapHandler.h"
#include "include/Transition.h"

class LevelManager
{
public:
    static LevelManager& GetManager();
    LevelManager();
    void Update();
    std::vector<Rectangle> GetCollidersRec();
    std::vector<GateData> GetGateCollidersRec();
    void OnGateCollision(GateData Data);
    Vector2 GetPlayerPosition();

private:
    MapHandler *Map;
    void CaveTransition(std::string Path);
};