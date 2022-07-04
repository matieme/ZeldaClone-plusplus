#include <string>
#include <raylib.h>
#include "libs/tileson.hpp"

class MapHandler {
    tson::Map map;
    Texture2D map_tex;
    tson::Tileset *map_tileset;

public:
    Vector2 player_init_pos;

    MapHandler(std::string file);

    void dibujar();
};
