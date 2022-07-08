#pragma once
#include "include/MapHandler.h"

class LevelManager
{
public:
    static LevelManager& GetManager();
    LevelManager();
    void DrawCurrentMap();
    std::vector<Rectangle> GetCollidersRec();

private:
    MapHandler *Map;

};