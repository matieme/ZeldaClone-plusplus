#include "raylib.h"
#include "include/Player.h"
#include "include/InputManager.h"
#include "include/MapHandler.h"

int windowsDimensions[2]{512, 448};
MapHandler *Map;

int main()
{
    InputManager& InputManagerInstance = InputManager::GetManager();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Zelda Clone Game");

    Map = new MapHandler("src/resources/maps/Map_01.json");
    
    Player link = Player();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        InputManagerInstance.UpdateInput();
        BeginDrawing();
        ClearBackground(BLACK);

        Map->DrawMap();
        link.Update(InputManagerInstance);

        EndDrawing();
    }

    //UnloadTexture(map);
    link.Destroy();
    CloseWindow();
}