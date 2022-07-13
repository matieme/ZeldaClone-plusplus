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

void LevelManager::OnGateCollision(GateData Data)
{
    std::string Path = "src/resources/maps/";
    Path.append(Data.gateID);
    Path.append(".json");

    if(Data.MapType == "Cave")
    {
        CaveTransition(Path);
    }
    else
    {
        Map->CreateMap(Path);
    }

}

Vector2 LevelManager::GetPlayerPosition()
{
    return Map->GetPlayerPositionOnMap();
}

void LevelManager::CaveTransition(std::string Path)
{
    Transition caveTransition = Transition(0.7f);

    //Make the black transition here

    while (caveTransition.TransitionInProgress())
    {
        caveTransition.OnUpdate();
    }

    Map->DestroyMapColliders();
    Map->CreateMap(Path);
}