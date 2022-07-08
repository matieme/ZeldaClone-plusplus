#include <string>
#include <raylib.h>
#include "libs/tileson.hpp"

class MapHandler 
{
public:
    MapHandler(std::string file);
    void DrawMap();
    void GenerateColliders();
    std::vector<Rectangle> GetMapColliderRec();
    void DrawColliderRectDebug();

private:
    tson::Map map;
    Texture2D map_tex;
    tson::Tileset *map_tileset;
    std::vector<Rectangle> CollidersRecs;
};
