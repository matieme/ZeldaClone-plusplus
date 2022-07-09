#pragma once
#include "include/MapHandler.h"

class LevelManager
{
public:
    static LevelManager& GetManager();
    LevelManager();
    void Update();
    std::vector<Rectangle> GetCollidersRec();
    std::vector<GateData> GetGateCollidersRec();
    void OnGateCollision();

private:
    MapHandler *Map;
};