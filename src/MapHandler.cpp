#include <iostream>
#include <cmath>
#include "include/MapHandler.h"
 
MapHandler::MapHandler(std::string file) 
{
    tson::Tileson parser;
    map = parser.parse(fs::path(file));

    if (map.getStatus() == tson::ParseStatus::OK) {

        for (auto &tileset : map.getTilesets()) 
        {
            const char* test = "src/resources/maps/Map_01.png"; //("src/resources/maps/" + tileset.getImage().string()).c_str();
            map_tex = LoadTexture(test);
            //map_tex = LoadTexture(fs::path("resources/maps/" + tileset.getImage().string()).c_str());
            map_tileset = &tileset;
        }

/*
        auto objs = map.getLayer("Objetos");
        tson::Object *player = objs->firstObj("player");
        player_init_pos.x = player->getPosition().x;
        player_init_pos.y = player->getPosition().y;

        std::cout << "Vida: " << player->get<int>("Vida") << std::endl;

        for (auto &obj : objs->getObjects()) {
            //Just iterate through all the objects
            std::cout << "Nombre: " << obj.getName() << std::endl;
            std::cout << "   Pos: " << obj.getPosition().x << std::endl;
        }
        */
    }

}

void MapHandler::dibujar() 
{
    Rectangle tile_rec;
    tile_rec.x = 0.0f;
    tile_rec.y = 0.0f;
    tile_rec.width = map.getTileSize().x;
    tile_rec.height = map.getTileSize().y;

    int firstId = map_tileset->getFirstgid(); //First tile id of the tileset
    int columns = map_tileset->getColumns(); //For the demo map it is 8.
    int margin = map_tileset->getMargin();
    int space = map_tileset->getSpacing();


    auto &c = map.getBackgroundColor();
    ClearBackground({c.r, c.g, c.b, c.a}); // Limpio la pantalla con blanco

    for (auto nombre: {"Background"}) 
    {
        auto *layer = map.getLayer(nombre);
        for (auto&[pos, tile] : layer->getTileData()) //Loops through absolutely all existing tiles
        {
            //Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
            //Would be unnecessary otherwise.
            if (tile != nullptr) {
                Vector2 position = {(float) std::get<0>(pos) * map.getTileSize().x,
                                           (float) std::get<1>(pos) * map.getTileSize().y};

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
