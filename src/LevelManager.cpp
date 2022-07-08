#include "include/LevelManager.h"

LevelManager& LevelManager::GetManager()
{
    static LevelManager instance;
    return instance;
}

LevelManager::LevelManager()
{
    Map = new MapHandler("src/resources/maps/Map_01.json");
}

void LevelManager::DrawCurrentMap()
{
    Map->DrawMap();
    Map->DrawColliderRectDebug();
}

std::vector<Rectangle> LevelManager::GetCollidersRec()
{
    return Map->GetMapColliderRec();   
}