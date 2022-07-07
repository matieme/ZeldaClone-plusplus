#include <iostream>
#include <cmath>
#include "include/MapHandler.h"

const char* MAPS_PATH = "src/resources/maps/";
const int MAP_OFFSET = 100; 

MapHandler::MapHandler(std::string file) 
{
    tson::Tileson parser;
    map = parser.parse(fs::path(file));

    if (map.getStatus() == tson::ParseStatus::OK) 
    {
        for (auto &tileset : map.getTilesets()) 
        {
            std::string TilesetImageFileName = tileset.getImage().string();
            const char* TilesetImageFileNameConst = TilesetImageFileName.c_str();
            
            char buffer[128];
            strncpy(buffer, MAPS_PATH, sizeof(buffer));
            strncat(buffer, TilesetImageFileNameConst, sizeof(buffer));
            const char* MapFileFullPath = buffer;
            
            map_tex = LoadTexture(MapFileFullPath);
            map_tileset = &tileset;
        }
    }

}

void MapHandler::DrawMap() 
{
    Rectangle tile_rec;
    tile_rec.x = 0.0f;
    tile_rec.y = 0.0f;
    tile_rec.width = map.getTileSize().x;
    tile_rec.height = map.getTileSize().y;

    int firstId = map_tileset->getFirstgid();
    int columns = map_tileset->getColumns();
    int margin = map_tileset->getMargin();
    int space = map_tileset->getSpacing();

    for (auto nombre: {"Background"}) 
    {
        auto *layer = map.getLayer(nombre);
        for (auto&[pos, tile] : layer->getTileData())
        {
            if (tile != nullptr) 
            {
                Vector2 position = {(float) std::get<0>(pos) * map.getTileSize().x,
                                           (float) std::get<1>(pos) * map.getTileSize().y + MAP_OFFSET};

                int baseTilePosition = (tile->getId() - firstId);

                int tileModX = (baseTilePosition % columns);
                int currentRow = (baseTilePosition / columns);
                int offsetX = tileModX * (map.getTileSize().x + space) + margin;
                int offsetY = currentRow * (map.getTileSize().y + space) + margin;

                tile_rec.x = offsetX;
                tile_rec.y = offsetY;
                DrawTextureRec(map_tex, tile_rec, position, WHITE);
            }
        }
    }
}
