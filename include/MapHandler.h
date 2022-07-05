#include <string>
#include <raylib.h>
#include "libs/tileson.hpp"

class MapHandler 
{
    tson::Map map;
    Texture2D map_tex;
    tson::Tileset *map_tileset;

public:
    MapHandler(std::string file);
    void DrawMap();
};
