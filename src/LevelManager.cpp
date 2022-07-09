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

void LevelManager::Update()
{
    Map->DrawMap();

    //Map colliders debug rectangles
    //Map->DrawColliderRectDebug();
}

std::vector<Rectangle> LevelManager::GetCollidersRec()
{
    return Map->GetMapColliderRec();
}

std::vector<GateData> LevelManager::GetGateCollidersRec()
{
    return Map->GetGatesColliderRec();
}

void LevelManager::OnGateCollision()
{

}