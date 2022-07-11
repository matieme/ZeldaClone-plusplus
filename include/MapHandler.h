#include <string>
#include <raylib.h>
#include "libs/tileson.hpp"
#include "include/GateData.h"

class MapHandler 
{
public:
    MapHandler(std::string file);
    void DrawMap();
    void GenerateColliders();
    std::vector<Rectangle> GetMapColliderRec();
    void DrawColliderRectDebug();
    std::vector<GateData> GetGatesColliderRec();
    void CreateMap(std::string file);
    void DestroyMapColliders();
    Vector2 GetPlayerPositionOnMap();

private:
    tson::Map map;
    Texture2D map_tex;
    tson::Tileset *map_tileset;
    std::vector<Rectangle> CollidersRecs;
    std::vector<GateData> CollidersGatesRecs;
};